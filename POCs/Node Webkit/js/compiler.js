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

exports.write = function(input) {
	if(global.compilerProcess != null) {
		exports.appendLogResult(input + "<br/>");
		global.compilerProcess.stdin.setEncoding = 'utf-8';
		global.compilerProcess.stdin.write(input + "\r\n");
	}
}

exports.run = function(code, execute) {
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
			// Stop old process
			exports.killCompiler();

			// Create new process
			var spawn = require('child_process').spawn;
			var compilerFilePath = exports.getCompilerFile();
			var arguments = [];

			if(execute) {
				arguments.push("-r");
			} else {
				arguments.push("-b");
			}

			if (global.settings.printTokenList) {
				arguments.push("-t");
			}

			if (global.settings.printCompilerList) {
				arguments.push("-c");
			}

			if (global.settings.printElapsedTime) {
				arguments.push("--time");
			}

			arguments.push(tempFile);
			var cmd = spawn(compilerFilePath, arguments);

			var errorOccurred = false;

			cmd.stdout.on('data', function (data) {
				data = data.toString();
				var resultWithBrs = data.replace(/(?:\r\n|\r|\n)/g, '<br/>');
				var resultWithSpaces = resultWithBrs.replace(/ /g, '&nbsp;');
				exports.appendLogResult(resultWithSpaces);

				// Show input field
				var input = '<div class="input">><input type="text"/></div>';
				var logDiv = $('#log');
				logDiv.html(logDiv.html() + input);
				
				setTimeout(function(){
					$("#log div.input input[type=text]").focus();
				}, 50);

				console.log(data);
				if(!errorOccurred) {
					var index = $('#log > div.tabs a[href="#output"]').parent().index();
					$("#log > div.tabs").tabs().tabs("option", "active", index);
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

				var index = $('#log > div.tabs a[href="#errors"]').parent().index();
				$("#log > div.tabs").tabs().tabs("option", "active", index);

				global.editor.getSession().setAnnotations(errors.map(function(error) {
					return {
						row: error.line-1,
						column: error.column,
						text: error.description.replace("&#9785;", ":("),
						type: (error.errorType) ? error.errorType.toLowerCase() : "error"
					}
				}));

				cmd.kill('SIGINT');
			});

			cmd.on('close', function (code) {
				exports.appendLogResult("<br>Program exited with code " + code + " <br>");
				$('#log .input').remove();
				global.editor.focus();
			});

			global.compilerProcess = cmd;
		}
	});
};

exports.killCompiler = function() {
	if(global.compilerProcess != null) {
		global.compilerProcess.kill('SIGINT');
	}
}

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
	outputDiv.stop(true, false).animate({ scrollTop: outputDiv.prop("scrollHeight")}, 300);
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
