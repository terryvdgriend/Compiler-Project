function init()
{
    global.$ = $;
    global.window = window;
    global.gui = require('nw.gui');
    global.debug = false;
    global.htmlToMarkdown = 0;
    global.compilerProcess = null;

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
        console.log("Settings saved:");
        console.log(global.settings);
    }

    global.setDefaultSettings = function() {
        global.settings = {};
        global.settings.version = 1.0;
        global.settings.theme = "twilight";
        global.settings.printTokenList = false;
        global.settings.printCompilerList = false;
        global.settings.printElapsedTime = false;
        global.settings.compilerFile = null;
        global.settings.customStyle = [
            {
                type: "constant",
                description: "Constants",
                color: ""
            },
            {
                type: "operator",
                description: "Operators",
                color: ""
            },
            {
                type: "variable",
                description: "Variables",
                color: ""
            },
            {
                type: "comment",
                description: "Comments",
                color: ""
            },
            {
                type: "type",
                description: "Types",
                color: ""
            },
            {
                type: "control",
                description: "Controllers",
                color: ""
            },
            {
                type: "function",
                description: "Functions",
                color: ""
            },
            {
                type: "paren",
                description: "Paren",
                color: ""
            },
            {
                type: "string",
                description: "Strings",
                color: ""
            },
            {
                type: "numeric",
                description: "Numeric",
                color: ""
            }
        ];
    }

	global.$(global.window.document).ready(function(){        
        global.setFile(null);
        global.setDefaultSettings();

        // Constants uitsplitten in functions en variables, PAREN toevoegen in CSS, string
        if(localStorage.settings != null) {
            var parsedJSON = JSON.parse(localStorage.settings);
            if(parsedJSON != null && typeof parsedJSON.version !== 'undefined' && parsedJSON.version == global.settings.version) {
                global.settings = parsedJSON;
            } else {
                global.saveSettings();
            }
        } else {
            global.saveSettings();
        }

        var menu = require("./../js/menu.js");      
        menu.initMenu();      
    });
    
    // Debug modus
    var option = {
        key : "Ctrl+0",
        active : function() {
            global.debug = !global.debug;
            if(global.debug) {
                global.gui.Window.get().showDevTools();
            }
        }
    };

    var shortcut = new global.gui.Shortcut(option);
    global.gui.App.registerGlobalHotKey(shortcut);
}