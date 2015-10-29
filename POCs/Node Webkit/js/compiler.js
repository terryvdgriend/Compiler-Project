exports.run = function(code) {
	global.editor.getSession().clearAnnotations();
	exports.clearLogResult();
	exports.clearErrorLog();
	$('body').addClass('showLog');
    global.editor.resize();

    // Get path
	var dir = global.require.main.filename.replace('/html/index.html', '');

    // Save temp file
    var fs = require('fs');
    var tempFile = dir + "/tempCode.md";
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

			exec(cmd, {maxBuffer: 25000000}, function(_error, stdout, stderr) {
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
					exports.appendErrorLog(errorHtml);

					var index = $('#log > div a[href="#errors"]').parent().index();
					$("#log > div").tabs("option", "active", index);

					global.editor.getSession().setAnnotations(errors.map(function(error) {
					    return {
					        row: error.line-1,
					        column: error.column,
					        text: error.description,
					        type: (error.errorType) ? error.errorType.toLowerCase() : "error"
					    }
					}));
				}

				var resultWithBrs = stdout.replace(/(?:\r\n|\r|\n)/g, '<br/>');
				var resultWithSpaces = resultWithBrs.replace(/ /g, '&nbsp;');
				exports.appendLogResult(resultWithSpaces);
				console.log(stdout);
				if(!stderr) {
					exports.appendLogResult("<br>Program finished! <br>");
					var index = $('#log > div a[href="#output"]').parent().index();
					$("#log > div").tabs("option", "active", index);
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
	$("#output").html("");
}

exports.setLogResult = function(html) {
	$("#output").html(html);
}

exports.appendLogResult = function(html) {
	$("#output").html($("#output").html() + html);
}

exports.clearErrorLog = function(html) {
	$("#errors").html("");
}

exports.setErrorLog = function(html) {
	$("#errors").html(html);
}

exports.appendErrorLog = function(html) {
	$("#errors").html($("#errors").html() + html);
}
