links = [
  'zoommtg://zoom.us/join?action=join&confno=[confno]&pwd=[hashed pw]',
  'zoommtg://zoom.us/join?action=join&confno=[confno]&pwd=[hashed pw]',
  'zoommtg://zoom.us/join?action=join&confno=[confno]&pwd=[hashed pw]',
  'zoommtg://zoom.us/join?action=join&confno=[confno]&pwd=[hashed pw]',
  'zoommtg://zoom.us/join?action=join&confno=[confno]&pwd=[hashed pw]',
  'zoommtg://zoom.us/join?action=join&confno=[confno]&pwd=[hashed pw]'
];

teachers = [
  'Teacher 1',
  'Teacher 2',
  'Teacher 3',
  'Teacher 4',
  'Teacher 5',
  'Teacher 6'
];

var args = process.argv.slice(2);

var link = links[args[0] - 1];
var teacher = teachers[args[0] - 1];

const cocoaDialog = require('cocoa-dialog');
const execSync = require('child_process').execSync;

(async () => {
	const result = await cocoaDialog('msgbox', {
		title: 'Launch Zoom Meeting',
		text: `Launch ${teacher}?`,
    button1: 'Yes',
    button2: 'No'
	});

  if (result === '1') {
    const output = execSync(`open "${link}"`, { encoding: 'utf-8' });
  }
})();
