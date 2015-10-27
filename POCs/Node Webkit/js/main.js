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

        textEditor.ace({ theme: 'twilight' })
        var ace = textEditor.data('ace').editor.ace;

        ace.getSession().on('change', function(e) {
            editor.reload();
        });

        $('#log a.close').on('click', function() {
            $('body').removeClass('showLog');
            ace.resize();
        });
    });
}

