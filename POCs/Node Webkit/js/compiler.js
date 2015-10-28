exports.run = function(code) {
	global.editor.getSession().clearAnnotations();
	exports.clearLogResult();
	$('body').addClass('showLog');
    global.editor.resize();

	compilerFile = "compiler\\Compiler-Windows.exe";
	if (process.platform === "darwin") {
		compilerFile = "./compiler/Compiler-OSX";
    }

	var exec = require('child_process').exec;
	var cmd = compilerFile + ' -c "' + code + '"';

	exec(cmd, {maxBuffer: 25000000}, function(error, stdout, stderr) {
		var resultWithBrs = stdout.replace(/(?:\r\n|\r|\n)/g, '<br/>');
		var resultWithSpaces = resultWithBrs.replace(/ /g, '&nbsp;');
		exports.setLogResult(resultWithSpaces);

		if(error || stderr) {
			var result = "<br><br>" + error + "<br><br>" + stderr;
			exports.appendLogResult(result);
			exports.appendLogResult(JSON.stringify(error));
			console.log(error);
		}
	});

	// var errors = [{row: 2, error: "Mooie error hoor!"}];
	// global.editor.getSession().setAnnotations(errors.map(function(x) {
	//     return {
	//         row: x.row-1,
	//         column: 0,
	//         text: x.error,
	//         type: "error" // also warning and information
	//     }
	// }));

};

exports.parseData = function(data) {
	var data = data.toString();
	var resultWithBrs = data.replace(/(?:\r\n|\r|\n)/g, '<br/>');
	var resultWithSpaces = resultWithBrs.replace(/ /g, '&nbsp;');
	return resultWithSpaces;
}

exports.clearLogResult = function(html) {
	$("#log div").html("");
}

exports.setLogResult = function(html) {
	$("#log div").html(html);
}

exports.appendLogResult = function(html) {
	$("#log div").html($("#log div").html() + html);
}
