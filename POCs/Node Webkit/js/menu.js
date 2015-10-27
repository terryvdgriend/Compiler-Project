exports.initMenu = function() {
	var win = global.gui.Window.get();
    var menubar = new global.gui.Menu({ type: 'menubar' });
    var fileMenu = new global.gui.Menu();

    var editor = require("./../js/editor.js");
    var compiler = require("./../js/compiler.js");

    fileMenu.append(new global.gui.MenuItem({
        label: 'Nieuw',
        click: function() {
        	editor.loadText("");
        }
    }));
    fileMenu.append(new global.gui.MenuItem({
        label: 'Openen',
        click: function() {
        	editor.chooseFile("#openFileDialog", function(filename) {
        		editor.loadFile(filename);
        	});
        }
    }));
    fileMenu.append(new global.gui.MenuItem({
        label: 'Opslaan',
        click: function() {
            editor.chooseFile("#saveFileDialog", function(filename) {
                var fs = require('fs');
                fs.writeFile(filename, global.editor.getValue(), function(err) {
                    if (err) {
                        console.log(err);
                    } else {
                        console.log("The file was saved!");
                    }
                });
            });
        }
    }));
    fileMenu.append(new global.gui.MenuItem({
        label: 'Afsluiten',
        click: function() {
            global.gui.App.quit();
        }
    }));

    var programMenu = new global.gui.Menu();
    programMenu.append(new global.gui.MenuItem({
        label: 'Run',
        click: function() {
            $('body').addClass('showLog');
            compiler.run(global.editor.getValue());
            global.editor.resize();
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