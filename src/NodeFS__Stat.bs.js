// Generated by BUCKLESCRIPT, PLEASE EDIT WITH CARE
'use strict';

var Fs = require("fs");
var Curry = require("bs-platform/lib/js/curry.js");
var Relude_IO = require("relude/src/Relude_IO.bs.js");
var Caml_option = require("bs-platform/lib/js/caml_option.js");
var NodeFS__Error = require("./NodeFS__Error.bs.js");
var Relude_Result = require("relude/src/Relude_Result.bs.js");

function stat(path) {
  return Relude_IO.async((function (resolve) {
                Fs.stat(path, (function (error, data) {
                        return Curry._1(resolve, Curry._2(Relude_Result.mapError, NodeFS__Error.fromException, Relude_Result.flip(Relude_Result.fromOption(data, error === null ? undefined : Caml_option.some(error)))));
                      }));
                
              }));
}

exports.stat = stat;
/* fs Not a pure module */
