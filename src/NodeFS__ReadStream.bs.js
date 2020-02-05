// Generated by BUCKLESCRIPT, PLEASE EDIT WITH CARE
'use strict';

var Fs = require("fs");
var Curry = require("bs-platform/lib/js/curry.js");
var Relude_IO = require("relude/src/Relude_IO.bs.js");
var NodeFS__Error = require("./NodeFS__Error.bs.js");
var Relude_Js_Promise = require("relude/src/js/Relude_Js_Promise.bs.js");

function make(path) {
  return Relude_IO.mapError(NodeFS__Error.fromException, Relude_Js_Promise.toIOLazy((function (param) {
                    return new Promise((function (resolve, reject) {
                                  var stream = Fs.createReadStream(path);
                                  stream.on("error", reject);
                                  stream.on("ready", (function (param) {
                                          return Curry._1(resolve, stream);
                                        }));
                                  return /* () */0;
                                }));
                  })));
}

var $$Error = /* alias */0;

var Utils = /* alias */0;

exports.$$Error = $$Error;
exports.Utils = Utils;
exports.make = make;
/* fs Not a pure module */
