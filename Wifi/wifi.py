import subprocess

def main():
    data = subprocess.check_output(['netsh','wlan','show','profiles']).decode('utf-8').split('\n')
    profiles = [i.split(":")[1][1:-1] for i in data if "All User Profile" in i]
    f = open("SavedPasswords.txt", "w")
    for i in profiles:
        try:
            results = subprocess.check_output(['netsh','wlan','show','profiles',f'name={i}','key=clear']).decode('utf-8').split('\n')
        except:
            continue
        results = [b.split(":")[1][1:-1] for b in results if "Key Content" in b]
        try:
            f.write("{:<30}|    {:<}\n".format(i,results[0]))
        except IndexError:
            f.write("{:<30}|    {:<}\n".format(i,""))
    f.close()

if __name__=="__main__":
    main()
