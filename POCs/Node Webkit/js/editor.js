exports.reload = function(){
    var marked = require("marked");
    marked.setOptions({
    renderer: new marked.Renderer(),
        gfm: true,
        tables: true,
        breaks: false,
        pedantic: false,
        sanitize: false,
        smartLists: true,
        smartypants: false
    });
    var resultDiv = global.$('#markdown');
    var textEditor = global.$('#editor textarea');
    var text = textEditor.val();
    resultDiv.html(marked(text));
};

exports.loadText = function(text) {
    var textEditor = global.$('#editor textarea');
    textEditor.val(text);
    exports.reload();
};

exports.loadFile = function(file) {
    var fs = require('fs');
    fs.readFile(file, 'utf8', function(err, data) {
        if (err) {
            return console.log(err);
        } else {
            console.log("The file was loaded!");
        }
        exports.loadText(data);
    });
};

exports.chooseFile = function(name, callback) {
    // Change event doesn't act the second time
    $(name).on("change", function(e) {
        val = $(name).val();
        $(name).val(null); 
        callback(val);
        return false;
    });

    $(name).trigger('click');       
};