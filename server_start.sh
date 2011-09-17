rm -rf build
node-waf -vv configure build && node app.js
