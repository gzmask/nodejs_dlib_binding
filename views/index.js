
/**
 * Module dependencies.
 */

var ejs = require('ejs')
  , fs = require('fs')
  , str = fs.readFileSync(__dirname + '/index.ejs', 'utf8');

var ret = ejs.render(str, {
  locals: {
    names: ['foo', 'bar', 'baz']
  }
});

console.log(ret);
