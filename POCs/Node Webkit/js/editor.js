exports.reload = function(){
    if(global.htmlToMarkdown > 0) {
        global.htmlToMarkdown--;
        return;
    }

    var marked = require("./plugins/marked/marked");
    var renderer = new marked.Renderer();
    marked.setOptions({
    renderer: renderer,
        gfm: true,
        tables: true,
        breaks: false,
        pedantic: false,
        sanitize: false,
        smartLists: true,
        smartypants: false
    });

    renderer.hr = function (text) {
        return "<hr data-code=\"" + text + "\">\n";
    }

    var resultDiv = global.$('#markdown #markdownCode');
    var code = global.editor.getValue();
    code = code.replace(/ {4}/gm, "");
    resultDiv.html(marked(code));   
};

exports.loadText = function(text) {
    global.editor.setValue(text);
    exports.reload();
};

exports.loadFile = function(file) {
    var fs = require('fs');
    fs.readFile(file, 'utf8', function(err, data) {
        if (err) {
            return console.log(err);
        } else {
            console.log("The file was loaded!");
            global.setFile(file);
        }
        exports.loadText(data);
    });
};

exports.chooseFile = function(name, callback) {
    // Change event doesn't act the second time
    $(name).on("change", function(e) {
        val = $(name).val();
        $(name).val(null); 
        if(val != "") {
            callback(val);
        }
        return false;
    });

    $(name).trigger('click');       
};

exports.saveFile = function(filename, callback) {
    global.fileName = filename;
    var fs = require('fs');
    fs.writeFile(filename, global.editor.getValue(), function(err) {
        if (err) {
            console.log(err);
        } else {
            console.log("The file was saved!");
        }
    });     
};