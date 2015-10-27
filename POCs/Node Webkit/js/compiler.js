exports.run = function(code) {
	compilerFile = "Compiler-Windows.exe";
	if (process.platform === "darwin") {
		compilerFile = "Compiler-OSX";
    }

	var exec = require('child_process').exec;
	var cmd = './compiler/' + compilerFile + ' -c "' + code + '"';
	console.log(cmd);
	
	exec(cmd, function(error, stdout, stderr) {
		if(error && stderr) {
			var result = "ERROR!" + "<br>" + error + "<br><br>" + stderr;
			console.log(result);
			exports.setLogResult(result);
		} else {
			var resultWithBrs = stdout.replace(/(?:\r\n|\r|\n)/g, '<br/>');
			var resultWithSpaces = resultWithBrs.replace(/ /g, '&nbsp;');
			exports.setLogResult(resultWithSpaces);
		}
	});
};

exports.setLogResult = function(result) {
	$("#log div").html(result);
}