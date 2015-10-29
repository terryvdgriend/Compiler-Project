exports.initMenu = function() {
	var win = global.gui.Window.get();
    var menubar = new global.gui.Menu({ type: 'menubar' });
    var fileMenu = new global.gui.Menu();

    var editor = require("./../js/editor.js");
    var compiler = require("./../js/compiler.js");

    fileMenu.append(new global.gui.MenuItem({
        label: 'Nieuw',
        key: "n",
        modifiers: (process.platform === "darwin") ? "cmd" : "ctrl",
        click: function() {
        	editor.loadText("");
            global.fileName = null;
        }
    }));
    fileMenu.append(new global.gui.MenuItem({
        label: 'Openen',
        key: "o",
        modifiers: (process.platform === "darwin") ? "cmd" : "ctrl",
        click: function() {
        	editor.chooseFile("#openFileDialog", function(filename) {
        		editor.loadFile(filename);
        	});
        }
    }));
    fileMenu.append(new global.gui.MenuItem({
        label: 'Opslaan',
        key: "s",
        modifiers: (process.platform === "darwin") ? "cmd" : "ctrl",
        click: function() {
            if(!global.fileName) {
                editor.chooseFile("#saveFileDialog", function(filename) {
                    editor.saveFile(filename);
                });
            } else {
                editor.saveFile(global.fileName);
            }
        }
    }));

    fileMenu.append(new gui.MenuItem({ type: 'separator' }));

    fileMenu.append(new global.gui.MenuItem({
        label: 'Afsluiten',
        click: function() {
            global.gui.App.quit();
        }
    }));

    var programMenu = new global.gui.Menu();
    programMenu.append(new global.gui.MenuItem({
        label: 'Run',
        key: "r",
        modifiers: (process.platform === "darwin") ? "cmd" : "ctrl",
        click: function() {
            compiler.run(global.editor.getValue());
        }
    }));

    programMenu.append(new gui.MenuItem({ type: 'separator' }));

    programMenu.append(new global.gui.MenuItem({
        label: 'Kies compiler',
        click: function() {
            compiler.chooseCompilerFile(function(file) {
                global.compilerFile = file;
            });
        }
    }));

    programMenu.append(new global.gui.MenuItem({
        label: 'Reset compiler file',
        click: function() {
            global.compilerFile = null;
        }
    }));

    //Allow CMD + A on OSX
    if (process.platform === "darwin") {
        menubar.createMacBuiltin('Down IDE', {
            hideEdit: false,
            hideWindow: true
        });
    }

    if (process.platform === "darwin") {
        menubar.insert(new global.gui.MenuItem({ label: 'Bestand', submenu: fileMenu }), 1);
    } else {
        menubar.append(new global.gui.MenuItem({ label: 'Bestand', submenu: fileMenu }));
    }

    menubar.append(new global.gui.MenuItem({ label: 'Programma', submenu: programMenu }));
    win.menu = menubar;
}