exports.run = function(code) {
	compilerFile = "Compiler-Windows";
	if (process.platform === "darwin") {
		compilerFile = "Compiler-OSX";
    }

	var exec = require('child_process').exec;
	var cmd = './compiler/' + compilerFile + ' -c "' + code + '"';

	exec(cmd, function(error, stdout, stderr) {
		var resultWithBrs = stdout.replace(/(?:\r\n|\r|\n)/g, '<br/>');
		var resultWithSpaces = resultWithBrs.replace(/ /g, '&nbsp;');
		exports.setLogResult(resultWithSpaces);
	});
};

exports.setLogResult = function(result) {
	$("#log div").html(result);
}