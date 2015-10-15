exports.initMenu = function() {
	var win = global.gui.Window.get();
    var menubar = new global.gui.Menu({ type: 'menubar' });
    var fileMenu = new global.gui.Menu();

    var editor = require("./../js/editor.js");

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
        		var textEditor = global.$('#editor');
        		fs.writeFile(filename, textEditor.val(), function(err) {
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

    menubar.append(new global.gui.MenuItem({ label: 'Bestand', submenu: fileMenu }));
    win.menu = menubar;
}