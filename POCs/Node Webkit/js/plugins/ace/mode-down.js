ace.define("ace/mode/matching_brace_outdent",["require","exports","module","ace/range"],function(e,t,n){"use strict";var r=e("../range").Range,i=function(){};(function(){this.checkOutdent=function(e,t){return/^\s+$/.test(e)?/^\s*\}/.test(t):!1},this.autoOutdent=function(e,t){var n=e.getLine(t),i=n.match(/^(\s*\})/);if(!i)return 0;var s=i[1].length,o=e.findMatchingBracket({row:t,column:s});if(!o||o.row==t)return 0;var u=this.$getIndent(e.getLine(o.row));e.replace(new r(t,0,t,s-1),u)},this.$getIndent=function(e){return e.match(/^\s*/)[0]}}).call(i.prototype),t.MatchingBraceOutdent=i}),ace.define("ace/mode/down_highlight_rules",["require","exports","module","ace/lib/oop","ace/mode/text_highlight_rules"],function(e,t,n){"use strict";var r=e("../lib/oop"),i=e("./text_highlight_rules").TextHighlightRules,s=function(){this.$rules={start:[{token:"string",regex:'["](?:(?:\\\\.)|(?:[^"\\\\]))*?["]'},{token:"paren",regex:"\-\-|\_\_|\\[|\\]"},{token:"comment",regex:">$",next:"start"},{token:"comment",regex:">",next:"singleLineComment"},{token:"keyword.operator",regex:"\\s(is|plus|minus|divide|(?:smaller|larger) than|like|in|increased|decreased|multiply|multiplied by|modulo|and gives|and|not|gets|with|or)(?!\\w)"},{token:"constant.function",regex:"### \\w+|addarraytodictionary|additemtoarrayat|addlengthtoarray|getitemfromarray|constanttoreturnvalue|getfromreturnvalue|identifiertoreturnvalue|printdown|printup|random|throwerror|getallfilesindirectory|getvideofilesindirectory|getaudiofilesindirectory|count|count|rename|removefile|removedirectory|movefile|movefiles|getfileextension|getdown|parseint"},{token:"constant.language",regex:"true|false|secret|default|case"},{token:"storage.type",regex:"_number_|_text_|_fact_"},{token:"variable.language",regex:"\\*\\*(.+?)\\*\\*"},{token:"constant.numeric",regex:"[+-]?\\d+(?:(?:\\.\\d*)?(?:[eE][+-]?\\d+)?)?\\b"},{token:"keyword.control",regex:"#### while|#### if|#### else if|#### else|#### switch|#### for|#### foreach|#### while|#### do"},{caseInsensitive: true}],comment:[{token:"comment",regex:".+"}],singleLineComment:[{token:"comment",regex:/\\$/,next:"singleLineComment"},{token:"comment",regex:/$/,next:"start"},{defaultToken:"comment"}]}};r.inherits(s,i),t.DownHighlightRules=s}),ace.define("ace/mode/down",["require","exports","module","ace/lib/oop","ace/mode/text","ace/tokenizer","ace/mode/matching_brace_outdent","ace/mode/down_highlight_rules"],function(e,t,n){"use strict";var r=e("../lib/oop"),i=e("./text").Mode,s=e("../tokenizer").Tokenizer,o=e("./matching_brace_outdent").MatchingBraceOutdent,u=e("./down_highlight_rules").DownHighlightRules,a=function(){this.HighlightRules=u,this.$outdent=new o};r.inherits(a,i),function(){this.lineCommentStart=">",this.getNextLineIndent=function(e,t,n){var r=this.$getIndent(t);return r},this.checkOutdent=function(e,t,n){return this.$outdent.checkOutdent(t,n)},this.autoOutdent=function(e,t,n){this.$outdent.autoOutdent(t,n)},this.createWorker=function(e){var t=new WorkerClient(["ace"],"ace/mode/mynew_worker","NewWorker");return t.attachToDocument(e.getDocument()),t.on("errors",function(t){e.setAnnotations(t.data)}),t}}.call(a.prototype),t.Mode=a})