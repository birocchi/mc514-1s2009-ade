
document.write("<link rel='apple-touch-icon' href='/images/apple-touch-icon.png' type='image/png' />");



var sbocustom = {

  popup:function(thepage) {
    var winl = (screen.width - 640) / 2;
    var wint = (screen.height - 450) / 4;
    winprops = 'height=450,width=640,top='+wint+',left='+winl+',toolbar=no,scrollbars='+'yes'+',resizable';

    win = window.open(thepage, 'sbopopup', winprops);

    if (parseInt(navigator.appVersion) >= 4) { win.window.focus(); }
  }

}




//NO_OBFUSCATE my_function_1

function my_function_1(text)
{
	alert(text);
}

/* The above has been tested using the following event handlers
<div style="margin:12px 0 12px 0;background:#FFFFCC;">
<a href="javascript:my_function_1('hello world');">Test href</a> 
| <a href="#" onclick="return my_function_1('hello world');">Test onclick</a>
| <a href="#" onclick="my_function_1('hello world');return false;">Test onclick 2</a>
| <a href="#" onmouseover="return my_function_1('hello world');">Test onmouseover</a>
</div>
*/


//NO_OBFUSCATE SafariFlashPopup()

function SafariFlashPopup() {
  self.name = "safaripopupparent";

  newwindow2=window.open('','flashDemo1','height=550,width=750,top=200,left=200');
  var tmp = newwindow2.document;
  tmp.write('<html><head><title>Safari Flash Demo</title>');
  tmp.write('<style type="text/css">body{padding: 10px;background:#000;color:#FFF;font-family:verdana,sans-serif;font-size:11px;}a{color:#FFF;text-decoration:none;font-weight:bold;}a:hover{text-decoration:underline;}</style>');
  tmp.write('</head><body><iframe id="demoflash" src="http://www.safaribooksonline.com/" width="700" height="450" marginwidth="0" marginheight="0" hspace="0" vspace="0" frameborder="1" scrolling="no"></iframe>');
  tmp.write('<p><a href="javascript:self.close();">Close Window</a></p>');
  tmp.write('</body></html>');
  tmp.close();
}

//NO_OBFUSCATE JavaOneRedirect()

function JavaOneRedirect() {
//document.url="http://www.somacon.com";
alert("TEST");
}


/* Simple Toggle for the B2B Self-service FAQ page */
var simpleTog = {

  tans:function(elemID) {
    if (!document.getElementById) return false;
    var myDiv = document.getElementById(elemID);
    if (myDiv){
      if (myDiv.style.display == 'none'){
        simpleTog.sans(elemID);
      } else{
        simpleTog.hans(elemID);
      }
    }
  },

  sans:function(elemID) {
    var myDiv = document.getElementById(elemID);
    if (myDiv){
      myDiv.style.display = "block";
    } else {
      return false;
    }
  },

  hans:function(elemID) {
    var myDiv = document.getElementById(elemID);
    if (myDiv){
      myDiv.style.display = "none";
    } else {
      return false;
    }
  }

}
