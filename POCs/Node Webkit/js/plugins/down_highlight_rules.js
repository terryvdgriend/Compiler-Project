define(function(require, exports, module) {
"use strict";

var oop = require("../lib/oop");
var TextHighlightRules = require("./text_highlight_rules").TextHighlightRules;

var DownHighlightRules = function() {

    // regexp must not have capturing parentheses. Use (?:) instead.
    // regexps are ordered -> the first match is used
   this.$rules = {
        "start" : [
            {
                token : "comment",
                regex : ">$",
                next : "start"
            }, {
                token : "comment",
                regex : ">",
                next : "singleLineComment"
            },
            {
                token : "keyword.operator",
                regex: "is|plus|minus|divide|(?:smaller|larger) than|like|in|increased|decreased|multiply|multiplied by|modulo|and gives|gets|with|or"
            },
            {
                token : "constant.function",
                regex : "### \\w+|printdown|random|printup"
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
            /*
            {
                token : "identifier",
                regex : "(#+ (?:else if|else|if|case|while|do|foreach|for)|and gives|multiplied by|(^>.*\n)|(smaller|larger) than|-?\\d\\.?\\d*|\"(.*?)\"|\n)"
            }
            */
        ],
        "comment" : [
            {
                token : "comment", // comment spanning whole line
                regex : ".+"
            }
        ],
        "singleLineComment" : [
            {
                token : "comment",
                regex : /\\$/,
                next : "singleLineComment"
            }, {
                token : "comment",
                regex : /$/,
                next : "start"
            }, {
                defaultToken: "comment"
            }
        ]
    };
};

oop.inherits(DownHighlightRules, TextHighlightRules);

exports.DownHighlightRules = DownHighlightRules;

});