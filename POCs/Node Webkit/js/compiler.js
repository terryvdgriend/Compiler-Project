exports.run = function(code) {
	console.log(code);

	var exec = require('child_process').exec;
	var cmd = './compiler/HelloMaurice';

	exec(cmd, function(error, stdout, stderr) {
		exports.setLogResult(stdout);
	});
};

exports.setLogResult = function(result) {
	$("#log div").html(result);
}