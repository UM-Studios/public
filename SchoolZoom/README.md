# Attending Each Period

These are just some scripts to automate attending each one of your school's periods.
This will only work on MacOS, however it should not be too difficult to make it work on some linux distro. Making it work on windows will be a bit tougher, but it is still possible. If you make it work on an OS that's not Mac, please submit a pull request so we can add it here!

## Instructions

1. After cloning the repository, you will need to have node and npm installed on your computer, then npm install cocoa-dialog.
2. In the `schoolZoom.js` file, replace the zoom links with your zoom links and the teachers with your teachers. Both arrays are arranged in the order of periods 1-6. The zoom links will look something like `zoommtg://zoom.us/join?action=join&confno=[confno]&pwd=[hashed pw]`. A normal zoom link will look something like `https://us04web.zoom.us/j/[confno]?pwd=[hashed pw]`. To fill in your own zoom links in the `schoolZoom.js` file, simply take the normal zoom link's confno and hashed pw and insert them into each link in the `schoolZoom.js` file.
For example, the zoom link `https://us04web.zoom.us/j/79243587155?pwd=QXc5RGcrUXA1Y0RubXJOYWZjQlJsQT09` would turn into `zoommtg://zoom.us/join?action=join&confno=79243587155&pwd=QXc5RGcrUXA1Y0RubXJOYWZjQlJsQT09`. 
If you the meeting doesn't have a password, just delete everything in the &pwd part of the links.
3. In the `attend.sh` file, change the path to `schoolZoom.js` to whatever the path to the file is on your machine.
4. Move the sh file to some directory in your path, such as `/usr/bin` or `/usr/local/bin`
5. Now, you should be able to type `attend.sh [period number]` anywhere in your terminal to go join some period's zoom. i.e `attend.sh 1` will bring you to your first period class.

## Optionally

You can hook this script up to automator and ical to make it automatically join each zoom meeting at the correct time. Follow this link: `https://smallbusiness.chron.com/schedule-automator-tasks-mac-os-x-39132.html`, and if you need help, because this is a bit of a confusing process, feel free to message us on instagram @_umstudios_ with any questions.
