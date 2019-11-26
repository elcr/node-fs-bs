// Generated by BUCKLESCRIPT, PLEASE EDIT WITH CARE
'use strict';

var Fs = require("fs");
var Block = require("bs-platform/lib/js/block.js");
var Curry = require("bs-platform/lib/js/curry.js");
var Rebase = require("@glennsl/rebase/src/Rebase.bs.js");
var FutureBS = require("future-bs/src/FutureBS.bs.js");
var Caml_option = require("bs-platform/lib/js/caml_option.js");
var NodeFS__Error = require("./NodeFS__Error.bs.js");
var NodeFS__JsError = require("./NodeFS__JsError.bs.js");
var Js_null_undefined = require("bs-platform/lib/js/js_null_undefined.js");

var DirectoryEntry = { };

function readDir(encoding, path) {
  return FutureBS.make((function (resolve) {
                var options = {
                  withFileTypes: true,
                  encoding: Js_null_undefined.fromOption(encoding)
                };
                Fs.readdir(path, options, (function (error, files) {
                        return Curry._1(resolve, Rebase.$$Option.getOr(/* Ok */Block.__(0, [files]), Rebase.$$Option.map((function (error) {
                                              return /* Error */Block.__(1, [NodeFS__Error.fromJsError(NodeFS__JsError.fromException(error))]);
                                            }), (error == null) ? undefined : Caml_option.some(error))));
                      }));
                return /* () */0;
              }));
}

var $$Error = 0;

var JsError = 0;

exports.$$Error = $$Error;
exports.JsError = JsError;
exports.DirectoryEntry = DirectoryEntry;
exports.readDir = readDir;
/* fs Not a pure module */
