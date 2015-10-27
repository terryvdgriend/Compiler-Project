exports.run = function(code) {
	compilerFile = "Compiler-Windows.exe";
	if (process.platform === "darwin") {
		compilerFile = "Compiler-OSX";
    }

	var exec = require('child_process').exec;
	var cmd = './compiler/' + compilerFile + ' -c "' + code + '"';
	
	exec(cmd, function(error, stdout, stderr) {
		var resultWithBrs = stdout.replace(/(?:\r\n|\r|\n)/g, '<br/>');
		var resultWithSpaces = resultWithBrs.replace(/ /g, '&nbsp;');
		exports.setLogResult(resultWithSpaces);

		if(error || stderr) {
			var result = "<br><br>" + error + "<br><br>" + stderr;
			exports.appendLogResult(result);
		}
	});
};

exports.setLogResult = function(html) {
	$("#log div").html(html);
}

exports.appendLogResult = function(html) {
	$("#log div").html($("#log div").html() + html);
}