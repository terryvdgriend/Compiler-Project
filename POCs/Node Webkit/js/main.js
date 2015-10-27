function init()
{
	global.$(global.window.document).ready(function(){
        var editor = require("./../js/editor.js");
        var compiler = require("./../js/compiler.js");
        var textEditor = global.$('#editor textarea');

		var menu = require("./../js/menu.js");
		menu.initMenu();

        var compile = global.$('#compile');

        compile.bind('click', function() {
            var som = require('./../cpp/Som');
            console.log('This should be eight: ', som.Add(3,5));
        });

        global.editor = ace.edit("code");
        global.editor.setTheme("ace/theme/twilight");
        global.editor.session.setMode("ace/mode/markdown");
        global.editor.setOptions({
            wrap : true,
            highlightSelectedWord: true,
            showPrintMargin: false,
            vScrollBarAlwaysVisible: false,
            fontSize: "15px",
            enableBasicAutocompletion: true,
            enableSnippets: true,
            enableLiveAutocompletion: true
        });

        global.editor.commands.addCommand({
            name: "Run",
            bindKey: {win: "Ctrl-R", mac: "Command-R"},
            exec: function(editor) {
                $('body').addClass('showLog');
                compiler.run(global.editor.getValue());
                global.editor.resize();
            }
        });

        var autoComplete = [
            { key: "if", value: "#### if" },
            { key: "else", value: "#### else" },
            { key: "else if", value: "#### else if" },
            { key: "for", value: "#### for" },
            { key: "foreach", value: "#### foreach" },
            { key: "while", value: "#### while" },
            { key: "do", value: "#### do" },
            { key: "smaller than", value: "smaller than" },
            { key: "larger than", value: "larger than" },
            { key: "getal", value: "_getal_" },
            { key: "tekst", value: "_tekst_" },
            { key: "fact", value: "_fact_" },
            { key: "variable", value: "_variable_" },
            { key: "declaration", value: "_declaration_" },
            { key: "function", value: "_function_" },
            { key: "class", value: "_class_" },
            { key: "namespace", value: "_namespace_" },
            { key: "_comment_", value: "_comment_" },
            { key: "plus", value: "plus" },
            { key: "increased", value: "increased" },
            { key: "minus", value: "minus" },
            { key: "decreased", value: "decreased" },
            { key: "divide", value: "divide" },
            { key: "multiply", value: "multiply" },
            { key: "modulo", value: "modulo" }
        ];
        
        var downCompleter = {
            getCompletions: function(editor, session, pos, prefix, callback) {
                if (prefix.length === 0) { callback(null, []); return }
                callback(null, autoComplete.map(function(ea) {
                    return {name: ea.key, value: ea.value, score: null, meta: null}
                }));
            }
        }
        
        var langTools = ace.require("ace/ext/language_tools");
        langTools.addCompleter(downCompleter);

        global.editor.on('change', function(e) {
            editor.reload();
        });

        $('#log a.close').on('click', function() {
            $('body').removeClass('showLog');
            global.editor.resize();
        });
    });
}

