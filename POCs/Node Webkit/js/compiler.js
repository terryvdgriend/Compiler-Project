exports.getCompilerFile = function() {
	var windowsCompiler = "Compiler-Windows.exe";
	var osxCompiler = "Compiler-OSX"

	compilerFilePath = "compiler\\" + windowsCompiler;
	if (process.platform === "darwin") {
		compilerFilePath = "./compiler/" + osxCompiler;
	}

	// Custom compiler defined
	if(global.settings.compilerFile != null) {
		if (process.platform === "darwin") {
			compilerFilePath = global.settings.compilerFile.replace(/ /g,"\\ ");
		} else {
			compilerFilePath = global.settings.compilerFile
		}
	}

	return compilerFilePath;
}

exports.run = function(code) {
	global.editor.getSession().clearAnnotations();
	exports.clearLogResult();
	exports.clearErrorLog();
	$('body').addClass('showLog');
	global.editor.resize();

	// Save temp file
	var fs = require('fs');
	var dirForTempCode = global.require.main.filename.replace('/html/index.html', '');
	var tempFile = dirForTempCode + "/tempCode.md";
	fs.writeFile(tempFile, global.editor.getValue(), function(err) {
		if (err) {
			console.log(err);
		} else {
			var spawn = require('child_process').spawn;
			var compilerFilePath = exports.getCompilerFile();
			var cmd = spawn(compilerFilePath, ['-f', tempFile]);

			var errorOccurred = false;

			cmd.stdout.on('data', function (data) {
				data = data.toString();
				var resultWithBrs = data.replace(/(?:\r\n|\r|\n)/g, '<br/>');
				var resultWithSpaces = resultWithBrs.replace(/ /g, '&nbsp;');
				exports.appendLogResult(resultWithSpaces);
				console.log(data);
				if(!errorOccurred) {
					var index = $('#log > div a[href="#output"]').parent().index();
					$("#log > div").tabs("option", "active", index);
				}
			});

			cmd.stderr.on('data', function (data) {
				errorOccurred = true;

				var errors = JSON.parse(data)
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

				cmd.kill('SIGINT');
			});

			cmd.on('close', function (code) {
				exports.appendLogResult("<br>Program exited with code " + code + " <br>");
			});
		}
	});
};

exports.getTokenList = function(callback) {
	var spawn = require('child_process').spawn;

	var compilerFilePath = exports.getCompilerFile();
	var cmd2 = spawn(compilerFilePath, ['getTokens']);

	cmd2.stdout.on('data', function (data) {
		var listString = data.toString();
		var list = JSON.parse(listString);
		callback(list);
	});

	cmd2.stderr.on('data', function (data) {
		cmd.kill('SIGINT');
		callback([]);
	});
};

exports.chooseCompilerFile = function(input, callback) {
	input.on("change", function(e) {
		val = $(this).val();
		if(val != "") {
			$(this).val(""); 
			callback(val);
		}
		return false;
	});

	input.trigger('click');       
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
	exports.logToBottom();
}

exports.appendLogResult = function(html) {
	var outputDiv = $('#output');
	outputDiv.html(outputDiv.html() + html);
	exports.logToBottom();
}

exports.logToBottom = function() {
	var outputDiv = $('#output');
	outputDiv.animate({ scrollTop: outputDiv.prop("scrollHeight")}, 300);
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
