var express = require('express');
var router = express.Router();
var bodyParser = require('body-parser');
var app = express();
var jsonParser = bodyParser.json();
var requestify = require('requestify');
var IS = require('initial-state');
var nodemailer = require('nodemailer');
var smtpTransport = require('nodemailer-smtp-transport');
global.disease=0;
 var bucket = IS.bucket('WSNProject', '7NWgod6vuE8L60n2R40pwOFQgacL4P1Z');
 var TMP36,pressure,humid;
   
var transporter = nodemailer.createTransport(smtpTransport({
    service: 'gmail',
    auth: {
        user: 'srg.ba6@gmail.com', // my mail
        pass: 'yatra@1234'
    }
}));
    var mailOptions = {
        from: '"Dashboard Admin" <srg.ba6@gmail.com>', // sender address
        to: 'siddg@ufl.edu', // list of receivers
        subject: 'Severe Weather Alert!', // Subject line
        text: 'Testing', // plaintext body
        html: '<b>This is to alert you that the current weather conditions increase the likelihood of your crops catching certain diseases. ' +
        'To avoid infestation, please spray pesticides at the earliest.' + 
        '<br><br>To view the latest weather conditions, kindly go to the <a href="https://wsn-keer.c9users.io/">dashboard</a>.</b>' // html body
    };
 
/* GET home page. */
router.get('/', function(req, res, next) {
res.useChunkedEncodingByDefault = false;
    console.log(req.query);
     TMP36 =  req.query.t;
     humid = req.query.h;
     pressure = req.query.p;
   
    if(TMP36!=null)
    bucket.push('TMP36', TMP36);
    if(humid!=null)
    bucket.push('humid', humid);
    if(pressure!=null)
    bucket.push('pressure', pressure);

res.render('index');

if(humid>70) {
    global.disease="true";
// send mail with defined transport object
   
   
    transporter.sendMail(mailOptions, function (error, info) {
        if (error) {
            return console.log(error);
        }
        console.log('Message sent: ' + info.response);
    });
}
else if(humid==0||humid<=70) global.disease="false";
    console.log(global.disease);
    
      });





router.post('/', function(req, res, next) {

    res.render('index');
});



module.exports = router;
