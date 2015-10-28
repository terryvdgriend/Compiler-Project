exports.run = function(code) {
	global.editor.getSession().clearAnnotations();
	exports.clearLogResult();
	$('body').addClass('showLog');
    global.editor.resize();

    // Get path
	var dir = global.require.main.filename.replace('/html/index.html', '');

    // Save temp file
    var fs = require('fs');
    var tempFile = dir + "/tempCode.md";
    console.log(tempFile);
    fs.writeFile(tempFile, global.editor.getValue(), function(err) {
        if (err) {
            console.log(err);
        } else {
			compilerFile = "compiler\\Compiler-Windows.exe";
			if (process.platform === "darwin") {
				compilerFile = "./compiler/Compiler-OSX";
		    }

			var exec = require('child_process').exec;
			var cmd = compilerFile + ' -f ' + '"' + tempFile + '"';
			console.log(cmd);

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
        }
    });
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
