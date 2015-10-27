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
            enableLiveAutocompletion: false
        });

        global.editor.on('change', function(e) {
            editor.reload();
        });

        $('#log a.close').on('click', function() {
            $('body').removeClass('showLog');
            global.editor.resize();
        });
    });
}

