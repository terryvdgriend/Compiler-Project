function init()
{
	global.$(global.window.document).ready(function(){
        var editor = require("./../js/editor.js");
        var textEditor = global.$('#editor');

        textEditor.bind('input propertychange', function() {
            editor.reload();
        });

		var menu = require("./../js/menu.js");
		menu.initMenu();

        var compile = global.$('#compile');

        compile.bind('click', function() {
            var som = require('./../cpp/Som');
            console.log('This should be eight: ', som.Add(3,5));
        });
    });
}