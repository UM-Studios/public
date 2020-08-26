
const cocoaDialog = require('cocoa-dialog');
const execSync = require('child_process').execSync;

(async () => {
    const result = await cocoaDialog('standard-inputbox', {
        title: 'Join Zoom',
        'informative-text': "Enter zoom link:"
    });
    if(result != 2)
    {
        let regID = new RegExp('(?<=\/j\/)[0-9]*');
        let regPW = new RegExp('(?<=pwd=)[0-9a-zA-Z]*');
        let id = regID.exec(result);
        let pw = regPW.exec(result)
        let link = 'zoommtg://zoom.us/join?action=join&confno=' + id + '&pwd=' + pw;
        const output = execSync(`open "${link}"`, {encoding: 'utf-8'});
    }

})();