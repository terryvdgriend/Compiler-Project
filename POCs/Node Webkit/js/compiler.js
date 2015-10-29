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

			exec(cmd, {maxBuffer: 25000000}, function(_error, stdout, stderr) {
				var resultWithBrs = stdout.replace(/(?:\r\n|\r|\n)/g, '<br/>');
				var resultWithSpaces = resultWithBrs.replace(/ /g, '&nbsp;');
				exports.setLogResult(resultWithSpaces);

				if(stderr) {
					var errors = JSON.parse(stderr)
					console.log(errors);
					
					errorHtml = "<table class=\"errors\" cellspacing=\"0\">"

					for (var i = 0; i < errors.length; i++) {
						var error = errors[i];
						var errorType = (error.errorType) ? error.errorType : "Uknown type";
						errorHtml += "<tr data-line=\"" + error.line + "\" data-column=\"" + error.column + "\">";
						errorHtml += "<td width=\"120\"><b>" + errorType + "</b></td>";
						errorHtml += "<td>" + error.description + "</td>";
						errorHtml += "<td style=\"text-align: right;\">on line " + error.line + ", column " + error.column + "</td>";
						errorHtml += "</tr>";
					}

					errorHtml += "</table>";
					exports.appendLogResult(errorHtml);			
					
					global.editor.getSession().setAnnotations(errors.map(function(error) {
					    return {
					        row: error.line-1,
					        column: error.column,
					        text: error.description,
					        type: (error.errorType) ? error.errorType.toLowerCase() : "error"
					    }
					}));
				} else {
					exports.appendLogResult("Program finished! <br>");
				}
			});
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
