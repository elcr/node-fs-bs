// Generated by BUCKLESCRIPT, PLEASE EDIT WITH CARE
'use strict';

var Fs = require("fs");
var Curry = require("bs-platform/lib/js/curry.js");
var Relude_IO = require("relude/src/Relude_IO.bs.js");
var Caml_option = require("bs-platform/lib/js/caml_option.js");
var NodeFS__Error = require("./NodeFS__Error.bs.js");
var Relude_Result = require("relude/src/Relude_Result.bs.js");

var DirectoryEntry = { };

function readDir($staropt$star, path) {
  var encoding = $staropt$star !== undefined ? $staropt$star : "utf-8";
  return Relude_IO.async((function (resolve) {
                Fs.readdir(path, {
                      withFileTypes: true,
                      encoding: encoding
                    }, (function (error, files) {
                        return Curry._1(resolve, Curry._2(Relude_Result.mapError, NodeFS__Error.fromException, Relude_Result.flip(Relude_Result.fromOption(files, error === null ? undefined : Caml_option.some(error)))));
                      }));
                return /* () */0;
              }));
}

var $$Error = /* alias */0;

var Utils = /* alias */0;

exports.$$Error = $$Error;
exports.Utils = Utils;
exports.DirectoryEntry = DirectoryEntry;
exports.readDir = readDir;
/* fs Not a pure module */
