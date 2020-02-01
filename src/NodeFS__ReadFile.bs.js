// Generated by BUCKLESCRIPT, PLEASE EDIT WITH CARE
'use strict';

var Fs = require("fs");
var Relude_IO = require("relude/src/Relude_IO.bs.js");
var Caml_option = require("bs-platform/lib/js/caml_option.js");
var NodeFS__Error = require("./NodeFS__Error.bs.js");
var Relude_Result = require("relude/src/Relude_Result.bs.js");
var Relude_Js_Promise = require("relude/src/js/Relude_Js_Promise.bs.js");

function readFile($staropt$star, path) {
  var encoding = $staropt$star !== undefined ? $staropt$star : "utf-8";
  return Relude_IO.mapError(NodeFS__Error.fromException, Relude_Js_Promise.toIOLazy((function (param) {
                    return new Promise((function (resolve, reject) {
                                  Fs.readFile(path, {
                                        withFileTypes: true,
                                        encoding: encoding
                                      }, (function (error, contents) {
                                          Relude_Result.tapError(reject, Relude_Result.tapOk(resolve, Relude_Result.flip(Relude_Result.fromOption(contents, (error == null) ? undefined : Caml_option.some(error)))));
                                          return /* () */0;
                                        }));
                                  return /* () */0;
                                }));
                  })));
}

var $$Error = /* alias */0;

var Utils = /* alias */0;

exports.$$Error = $$Error;
exports.Utils = Utils;
exports.readFile = readFile;
/* fs Not a pure module */