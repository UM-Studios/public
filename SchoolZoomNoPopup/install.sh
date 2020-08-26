#!/usr/bin/env bash

which -s brew
if [[ $? != 0 ]] && ! command -v ggrep &> /dev/null
then
    echo "This script will need to install homebrew. If you are unsure what homebrew is, you can get a quick overview here: https://techstacker.com/what-is-homebrew/. If you will allow this script to install homebrew, type yes. Otherwise, type no. [yes/no]"
    agree=""
    while [[ agree != "yes" && agree != "no" ]]
    do
        read agree
        if [[ $agree == "no" ]]
        then
            exit 0
        elif [[ $agree != "yes" ]]
        then
            echo "Please enter yes or no."
        fi
    done
    /usr/bin/ruby -e "$(curl -fsSL https://raw.githubusercontent.com/Homebrew/install/master/install)"
    brew update
fi

if ! command -v ggrep &> /dev/null
then
    echo "This script needs to install ggrep (Don't worry, this is the last thing you'll have to install. If you are unsure what ggrep is, you can get a quick overview here: https://binx.io/blog/2018/11/19/learning-grep/. If you will allow this script to install ggrep, type yes. Otherwise, type no. [yes/no]"
    agree=""
    while [[ agree != "yes" && agree != "no" ]]
    do
        read agree
        if [[ agree == "no" ]]
        then
            exit 0
        elif [[ agree != "yes" ]]
        then
            echo "Please enter yes or no."
        fi
    done
fi

echo "Please the zoom links with single quotes around them for each of your period in order. If you would like to remove a link, type undo to remove the most recent. If you're done, type done.
For example,

'https://us04web.zoom.us/j/79243587155?pwd=QXc5RGcrUXA1Y0RubXJOYWZjQlJsQT09'
'https://us04web.zoom.us/j/79243587155?pwd=QXc5RGcrUXA1Y0RubXJOYWZjQlJsQT09'
'https://us04web.zoom.us/j/79243587155?pwd=QXc5RGcrUXA1Y0RubXJOYWZjQlJsQT09'
undo
'https://us04web.zoom.us/j/79243587155?pwd=QXc5RGcrUXA1Y0RubXJOYWZjQlJsQT09'
done
"

links=()

while [[ true ]]
do
    read link
    if [[ $link == "done" ]]
    then
        break
    fi

    if [[ $link == "undo" ]]
    then
        if [[ ${#links[@]} -eq 0 ]]
        then
            echo "Please enter a link before undoing."
            continue
        fi
        unset 'links[${#links[@]}-1]'
        printf "\n"
        echo "Current links:"
        printf '%s\n' "${links[@]}"
        printf "\n"
        continue
    fi
    links+=( $link )
    printf "\n"
    echo "Current links:"
    printf '%s\n' "${links[@]}"
    printf "\n"
done

periods=${#links[@]}

for (( i=1; i<=$periods; i++ ))
do
    file="zoomp$i.sh"
    
    echo "#!/usr/bin/env bash

    $PWD/zoom.sh 1" > $file

    chmod 700 $file
done

touch links.json
printf '%s\n' "${links[@]}" | jq -R . | jq -s . | sed "s/'//g" > links.json

echo "Please enter a period, what day, and what hour and minute (in 24 hour format space seperated) you wish to join the meeting. This time will be repeated every week. You can do as many of these as you need. If you wish to undo a previous time you schedule, type undo. Once you are done, type done.
For example:

1 1 10 15 <- This will schedule you to join period 1 every Monday at 10:15am
1 2 13 40 <- This will schedule you to join period 1 every Tuesday at 1:40pm
1 3 9 0   <- This will schedule you to join period 1 Every Wednesday at 9:00am
undo      <- This deletes the above task
done      <- This tells the program that you are done

In the above example, you will join period 1 every Monday at 10:15am and every Tuesday at 1:40pm.
"

periods=6

tasks=()
crons=()

while [[ true ]]
do
    read cmd 
    cmd=($cmd)
    if [[ ${cmd[0]} == "done" ]]
    then
        break
    fi
    if [[ ${cmd[0]} == "undo" ]]
    then
        if [[ ${#tasks[@]} -eq 0 ]]
        then
            echo "Please enter a time before undoing."
            continue
        fi
        unset 'crons[${#crons[@]}-1]'
        unset 'tasks[${#tasks[@]}-1]'
        printf "\n"
        echo "Current tasks:"
        printf '%s\n' "${tasks[@]}"
        printf "\n"
        continue
    fi
    re='^[0-9]+$'
    if [[ ${#cmd[@]} -ne 4 ]]
    then
        printf "\n"
        echo "Please enter 4 numbers."
        printf "\n"
        continue
    fi

    fail=0
    for (( i=0; i<4; i++ ))
    do
        if ! [[ ${cmd[$i]} =~ $re ]]
        then
            printf "\n"
            echo "Please enter numbers only"
            printf "\n"
            fail=1
            break
        fi  
    done

    if [[ fail -eq 1 ]]
    then
        continue
    fi

    if [[ ${cmd[0]} -lt 0 || ${cmd[0]} -gt $periods ]]
    then
        printf "\n"
        echo "Please enter a valid period."
        printf "\n"
        continue
    fi

    if [[ ${cmd[1]} -lt 1 || ${cmd[1]} -gt 7 ]]
    then
        printf "\n"
        echo "Please enter a valid day."
        printf "\n"
        continue
    fi

    if [[ ${cmd[2]} -lt 0 || ${cmd[2]} -gt 23 ]]
    then
        printf "\n"
        echo "Please enter a valid hour."
        printf "\n"
        continue
    fi

    if [[ ${cmd[3]} -lt 0 || ${cmd[3]} -gt 59 ]]
    then
        printf "\n"
        echo "Please enter a valid minute."
        printf "\n"
        continue
    fi
    
    crons+=("${cmd[3]} ${cmd[2]} * * ${cmd[1]} bash -lc $PWD/zoomp${cmd[0]}.sh")
    tasks+=("${cmd[0]} ${cmd[1]} ${cmd[2]} ${cmd[3]}")
    printf "\n"
    echo "Current tasks:"
    printf '%s\n' "${tasks[@]}"
    printf "\n"
done

echo "Your mac may ask you for administration permissions. This is on purpose, please click OK to finish the process."
sleep 2

crontab -l > mycron

for cron in "${crons[@]}"
do
  echo "$cron" >> mycron
done

crontab mycron
rm mycron

echo "You're all set! Thank you for using UM Studio's Zoom Meeting Scheduler. Follow us on our instagram @_umstudios_ for future content."
