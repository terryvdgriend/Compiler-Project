exports.initMenu = function() {
	var win = global.gui.Window.get();
    var menubar = new global.gui.Menu({ type: 'menubar' });
    var fileMenu = new global.gui.Menu();

    var editor = require("./../js/editor.js");
    var compiler = require("./../js/compiler.js");

    fileMenu.append(new global.gui.MenuItem({
        label: 'New File',
        key: "n",
        modifiers: (process.platform === "darwin") ? "cmd" : "ctrl",
        click: function() {
        	editor.loadText("");
            global.setFile(null);
        }
    }));
    fileMenu.append(new global.gui.MenuItem({
        label: 'Open...',
        key: "o",
        modifiers: (process.platform === "darwin") ? "cmd" : "ctrl",
        click: function() {
        	editor.chooseFile("#openFileDialog", function(filename) {
        		editor.loadFile(filename);
        	});
        }
    }));
    fileMenu.append(new global.gui.MenuItem({
        label: 'Save',
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
    fileMenu.append(new global.gui.MenuItem({
        label: 'Save as...',
        key: "s",
        modifiers: (process.platform === "darwin") ? "cmd shift" : "ctrl shift",
        click: function() {
            editor.chooseFile("#saveFileDialog", function(filename) {
                editor.saveFile(filename);
                global.setFile(filename);
            });
        }
    }));

    fileMenu.append(new gui.MenuItem({ type: 'separator' }));

    fileMenu.append(new global.gui.MenuItem({
        label: 'Quit',
        click: function() {
            global.gui.App.quit();
        }
    }));

    var settingsMenu = new global.gui.Menu();
    settingsMenu.append(new global.gui.MenuItem({
        label: 'Show settings...',
        click: function() {
            var win = global.gui.Window.open ('settings.html', {
              position: 'center',
              focus: true,
              frame: true,
              toolbar: global.debug
            });

            win.on ('loaded', function(){
                win.title = "Settings";
            });            
        }
    }));

    var programMenu = new global.gui.Menu();
    programMenu.append(new global.gui.MenuItem({
        label: 'Print tokenlist',
        type: 'checkbox',
        checked: global.settings.printTokenList,
        click: function() {
            global.settings.printTokenList = this.checked;
            global.saveSettings();
        }
    }));
    programMenu.append(new global.gui.MenuItem({
        label: 'Print compilerlist',
        type: 'checkbox',
        checked: global.settings.printCompilerList,
        click: function() {
            global.settings.printCompilerList = this.checked;
            global.saveSettings();
        }
    }));

    programMenu.append(new gui.MenuItem({ type: 'separator' }));
    programMenu.append(new global.gui.MenuItem({
        label: 'Run',
        key: "r",
        modifiers: (process.platform === "darwin") ? "cmd" : "ctrl",
        click: function() {
            compiler.run(global.editor.getValue());
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
        menubar.insert(new global.gui.MenuItem({ label: 'File', submenu: fileMenu }), 1);
    } else {
        menubar.append(new global.gui.MenuItem({ label: 'File', submenu: fileMenu }));
    }

    menubar.append(new global.gui.MenuItem({ label: 'Settings', submenu: settingsMenu }));
    menubar.append(new global.gui.MenuItem({ label: 'Program', submenu: programMenu }));
    win.menu = menubar;
}