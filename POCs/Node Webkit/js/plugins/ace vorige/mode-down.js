ace.define("ace/mode/matching_brace_outdent",["require","exports","module","ace/range"], function(require, exports, module) {
"use strict";

var Range = require("../range").Range;

var MatchingBraceOutdent = function() {};

(function() {

    this.checkOutdent = function(line, input) {
        if (! /^\s+$/.test(line))
            return false;

        return /^\s*\}/.test(input);
    };

    this.autoOutdent = function(doc, row) {
        var line = doc.getLine(row);
        var match = line.match(/^(\s*\})/);

        if (!match) return 0;

        var column = match[1].length;
        var openBracePos = doc.findMatchingBracket({row: row, column: column});

        if (!openBracePos || openBracePos.row == row) return 0;

        var indent = this.$getIndent(doc.getLine(openBracePos.row));
        doc.replace(new Range(row, 0, row, column-1), indent);
    };

    this.$getIndent = function(line) {
        return line.match(/^\s*/)[0];
    };

}).call(MatchingBraceOutdent.prototype);

exports.MatchingBraceOutdent = MatchingBraceOutdent;
});

ace.define("ace/mode/down_highlight_rules",["require","exports","module","ace/lib/oop","ace/mode/text_highlight_rules"], function(require, exports, module) {
"use strict";

var oop = require("../lib/oop");
var TextHighlightRules = require("./text_highlight_rules").TextHighlightRules;

var DownHighlightRules = function() {
   this.$rules = {
        "start" : [
            {
                token : "keyword.operator",
                regex: "is|plus|minus|divide|(?:smaller|larger) than|like|in|increased|decreased|multiply|multiplied by|modulo|and gives|gets|with"
            },
            {
                token : "support.function",
                regex : "printdown|random|printup"
            },
            {
                token : "constant.language",
                regex : "true|false|secret|default|case"
            },
            {
                token : "storage.type",
                regex: "_number_|_text_|_fact_"
            },
            {
                token : "variable.language",
                regex : "\\*\\*(.+?)\\*\\*"
            },
            {
                token : "constant.numeric",
                regex : "[+-]?\\d+(?:(?:\\.\\d*)?(?:[eE][+-]?\\d+)?)?\\b"
            },
            {
                token : "keyword.control",
                regex : "#### while|#### if|#### else if|#### else|#### switch|#### for|#### foreach|#### while|#### do"
            },
        ]
    };
};

oop.inherits(DownHighlightRules, TextHighlightRules);

exports.DownHighlightRules = DownHighlightRules;

});

ace.define("ace/mode/down",["require","exports","module","ace/lib/oop","ace/mode/text","ace/tokenizer","ace/mode/matching_brace_outdent","ace/mode/down_highlight_rules"], function(require, exports, module) {
"use strict";

var oop = require("../lib/oop");
var TextMode = require("./text").Mode;
var Tokenizer = require("../tokenizer").Tokenizer;
var MatchingBraceOutdent = require("./matching_brace_outdent").MatchingBraceOutdent;
var DownHighlightRules = require("./down_highlight_rules").DownHighlightRules;

var Mode = function() {
    this.HighlightRules = DownHighlightRules;
    this.$outdent = new MatchingBraceOutdent();
};
oop.inherits(Mode, TextMode);

(function() {
    this.lineCommentStart = "//";
    this.blockComment = {start: "/*", end: "*/"};
    this.getNextLineIndent = function(state, line, tab) {
        var indent = this.$getIndent(line);
        return indent;
    };

    this.checkOutdent = function(state, line, input) {
        return this.$outdent.checkOutdent(line, input);
    };

    this.autoOutdent = function(state, doc, row) {
        this.$outdent.autoOutdent(doc, row);
    };
    this.createWorker = function(session) {
        var worker = new WorkerClient(["ace"], "ace/mode/mynew_worker", "NewWorker");
        worker.attachToDocument(session.getDocument());
        worker.on("errors", function(e) {
            session.setAnnotations(e.data);
        });
        return worker;
    };
    
}).call(Mode.prototype);

exports.Mode = Mode;
});
