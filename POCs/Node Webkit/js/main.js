function init()
{
    global.$ = $;
    global.window = window;
    global.gui = require('nw.gui');

    global.alert = function(text) {
        alert(text);
    }

    global.goToPage = function(page) {
        $.ajax({
            url: page + '.html',
            type: 'GET',
            dataType: 'html'
        })
        .done(function(data) {
            $('#page').html(data);
            console.log("success");
        })
        .fail(function() {
            console.log("error");
        })
    }

    global.setFile = function(filePath) {
        global.fileName = null;

        var win = global.gui.Window.get();
        if(filePath) {
            var splitted = filePath.split("/");
            var file = splitted[splitted.length-1];
            
            win.title = "Down IDE - " + file;
        } else {
            win.title = "Down IDE - Untitled file";
        }
    }

    global.saveSettings = function() {
        localStorage.settings = JSON.stringify(global.settings);
    }

	global.$(global.window.document).ready(function(){        
        global.setFile(null);

        global.settings = {};
        global.settings.theme = "twilight";
        global.settings.printTokenList = false;
        global.settings.printCompilerList = false;
        global.settings.compilerFile = null;

        if(localStorage.settings != null) {
            var parsedJSON = JSON.parse(localStorage.settings);
            if(parsedJSON != null) {
                global.settings = JSON.parse(localStorage.settings);
            } else {
                global.saveSettings();
            }
        } else {
            global.saveSettings();
        }

        var menu = require("./../js/menu.js");      
        menu.initMenu();      
    });
}
