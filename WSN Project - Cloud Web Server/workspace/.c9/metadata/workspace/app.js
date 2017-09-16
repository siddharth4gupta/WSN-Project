{"filter":false,"title":"app.js","tooltip":"/app.js","undoManager":{"mark":0,"position":0,"stack":[[{"start":{"row":0,"column":0},"end":{"row":46,"column":0},"action":"remove","lines":["var express = require('express');","var path = require('path');","var favicon = require('serve-favicon');","var logger = require('morgan');","var cookieParser = require('cookie-parser');","var bodyParser = require('body-parser');","","var index = require('./routes/index');","var users = require('./routes/users');","","var app = express();","","// view engine setup","app.set('views', path.join(__dirname, 'views'));","app.set('view engine', 'jade');","","// uncomment after placing your favicon in /public","//app.use(favicon(path.join(__dirname, 'public', 'favicon.ico')));","app.use(logger('dev'));","app.use(bodyParser.json());","app.use(bodyParser.urlencoded({ extended: false }));","app.use(cookieParser());","app.use(express.static(path.join(__dirname, 'public')));","","app.use('/', index);","app.use('/users', users);","","// catch 404 and forward to error handler","app.use(function(req, res, next) {","  var err = new Error('Not Found');","  err.status = 404;","  next(err);","});","","// error handler","app.use(function(err, req, res, next) {","  // set locals, only providing error in development","  res.locals.message = err.message;","  res.locals.error = req.app.get('env') === 'development' ? err : {};","","  // render the error page","  res.status(err.status || 500);","  res.render('error');","});","","module.exports = app;",""],"id":2},{"start":{"row":0,"column":0},"end":{"row":51,"column":0},"action":"insert","lines":["var express = require('express');","var path = require('path');","var favicon = require('serve-favicon');","var logger = require('morgan');","var cookieParser = require('cookie-parser');","var bodyParser = require('body-parser');","","var index = require('./routes/index');","var cddl= require('./routes/cddl');","var BBB1= require('./routes/BBB1');","var BBB2= require('./routes/BBB2');","var getrequest= require('./routes/getrequest');","var app = express();","","// view engine setup","app.set('views', path.join(__dirname, 'views'));","app.set('view engine', 'ejs');","","// uncomment after placing your favicon in /public","//app.use(favicon(path.join(__dirname, 'public', 'favicon.ico')));","app.use(logger('dev'));","app.use(bodyParser.json());","app.use(bodyParser.urlencoded({ extended: false }));","app.use(cookieParser());","app.use(express.static(path.join(__dirname, 'public')));","","","app.use('/', index);","app.use('/cddl', cddl);","app.use('/BBB1', BBB1);","app.use('/BBB2', BBB2);","app.use('/action', getrequest);","// catch 404 and forward to error handler","app.use(function(req, res, next) {","  var err = new Error('Not Found');","  err.status = 404;","  next(err);","});","","// error handler","app.use(function(err, req, res, next) {","  // set locals, only providing error in development","  res.locals.message = err.message;","  res.locals.error = req.app.get('env') === 'development' ? err : {};","","  // render the error page","  res.status(err.status || 500);","  res.render('error');","});","","module.exports = app;",""]}]]},"ace":{"folds":[],"scrolltop":420,"scrollleft":0,"selection":{"start":{"row":0,"column":0},"end":{"row":51,"column":0},"isBackwards":false},"options":{"guessTabSize":true,"useWrapMode":false,"wrapToView":true},"firstLineState":{"row":23,"state":"start","mode":"ace/mode/javascript"}},"timestamp":1481419964997,"hash":"29630791a100ce086405e151ecc6b3975f7c7dd0"}