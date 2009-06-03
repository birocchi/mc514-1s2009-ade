function findPosX(obj)
{
    var curleft = 0;
	if (obj.offsetParent)
	{
		while (obj.offsetParent)
		{
			curleft += obj.offsetLeft;
			obj = obj.offsetParent;
		}
	}
	else if (obj.x)
        curleft += obj.x;
	return curleft;
}

function findPosY(obj)
{
	var curtop = 0;
	if (obj.offsetParent)
	{
		while (obj.offsetParent)
		{
			curtop += obj.offsetTop;
			obj = obj.offsetParent;
		}
	}
	else if (obj.y)
		curtop += obj.y;
	return curtop;
}	

function getUserAgentVersion(userAgent, versionName)
{
	var version = 0.0;
	var tempStr = userAgent.toLowerCase();
	var pos = tempStr.indexOf(versionName);
		
	if (pos != -1) 
	{
		var versionStr = tempStr.substring(pos + versionName.length,tempStr.length);
		if (versionStr.indexOf(" ") > -1)
			version = parseFloat(versionStr.substring(0, versionStr.indexOf(" ")));
		else
			version = parseFloat(versionStr);
	}
	return version;
}

function AjaxDropDown()
{
    this.Init = function(instanceName, anchorControlId, dropdownId, url)
    {
        this.turnoffMessage1 = "TURN SUGGESTIONS OFF";
        this.turnoffMessage2 = "(adjust preferences in My Safari)";
        if (this.isipuser && this.isipuser == true)
            this.turnoffMessage2 = "(adjust preferences in Desktop)";
        this.instanceName = instanceName;
        this.anchorControlId = anchorControlId;
        this.dropdownId = dropdownId;
        this.url = url;
        this.isIE = false;
        this.hideDelay = 300;
        this.timer = null;
        this.lastQuery = "";
        this.active = true;
        if (window.XMLHttpRequest) 
            this.httpReq = new XMLHttpRequest();
                  
        var dropdown = document.getElementById(this.dropdownId);
        dropdown.style.display = "none";
        dropdown.style.position = "absolute";
            
        var ua = navigator.userAgent.toLowerCase(); 
        if (ua.indexOf("safari") > -1)
        {
            dropdown.style.top = "auto";
            dropdown.style.left = "auto";
            dropdown.style['marginTop'] = "20px";
            
            // disable dropdown for older safari versions (known to crash)
            if (getUserAgentVersion(ua, "applewebkit/") < 418.9 || getUserAgentVersion(ua, "safari/") < 419.3)
                this.active = false;				
        }
        else
        {
            dropdown.style.top = "auto";
            dropdown.style.left = "auto";
        }

        if (navigator.product == "Gecko" && ua.indexOf('webkit') == -1)
        {
            var thisObj = this;
            document.getElementById(this.anchorControlId).addEventListener("keypress", function (event) { thisObj.keyPress(event); }, false);
            document.getElementById(this.anchorControlId).addEventListener("blur", function () { thisObj.Hide(); },false);
        } 
        else
        {
            var thisObj = this;
            try
            {
                document.getElementById(this.anchorControlId).attachEvent('onkeydown', function (event) { thisObj.keyPress(event); });
                document.getElementById(this.anchorControlId).attachEvent('onblur', function () { thisObj.Hide(); });
                this.isIE = true;
            }
            catch (E)
            {
                //for Konqueror
                document.getElementById(this.anchorControlId).onkeydown = function (event) { thisObj.keyPress(event); };
                document.getElementById(this.anchorControlId).onblur = function () { thisObj.Hide(); };
            }
        }
        document.getElementById(this.anchorControlId).setAttribute("autocomplete","off");      
    }
      
    this.Hide = function() 
    {
        var thisObj = this;
        window.setTimeout(function() { thisObj.hideDropDown(); }, this.hideDelay);
    }
      
    this.hideDropDown = function() 
    {
        if (document.all)
            this.closeShim(document.getElementById(this.dropdownId));
        document.getElementById(this.dropdownId).style.display = "none";
        var activeLine = document.getElementById("DropDownActive");
        if (activeLine) 
            activeLine.removeAttribute("id");
    }

    this.keyPress = function(event) 
    {
        if (this.active == false)
            return;

        if (this.DisableSuggest && this.DisableSuggest())
            return;

        if (event.keyCode == 13)
        {
            highlight = document.getElementById("DropDownActive");
			if (!highlight || highlight.firstChild.data != this.turnoffMessage1)
				this.Start(event);
			else
			{
				if (!this.isIE) 
					event.preventDefault();
				this.Hide();
				if (this.TurnOff)
					this.TurnOff();
			}
        }
        else if (event.keyCode == 40 || event.keyCode == 63233)
        {
            highlight = document.getElementById("DropDownActive");
            if (!highlight)
                highlight = document.getElementById(this.dropdownId + "_inner").firstChild.firstChild;
            else 
            {
                highlight.removeAttribute("id");
                if (highlight.nextSibling)
                {
					var dta = highlight.nextSibling.firstChild.data;
					if (escape(dta) == "%A0")
						highlight = highlight.nextSibling.nextSibling;
					else
					{
						if (dta == this.turnoffMessage2)
						{
							highlight.setAttribute("id","DropDownActive");
							return;
						}
						else
							highlight = highlight.nextSibling;
					}
                }
            }
            
            if (highlight) 
            {
                highlight.setAttribute("id","DropDownActive");
                var res = document.getElementById(this.dropdownId);
                if (highlight.offsetTop + highlight.offsetHeight > res.scrollTop + res.offsetHeight)
                    res.scrollTop = highlight.offsetTop - res.offsetHeight + highlight.offsetHeight;
            }

            if (!this.isIE) 
                event.preventDefault();

            if (highlight && highlight.firstChild.data != this.turnoffMessage1)
                this.SelectionChanged(highlight.firstChild.data);
        }
        else if (event.keyCode == 38 || event.keyCode == 63232) 
        {
            highlight = document.getElementById("DropDownActive");
            if (!highlight)
                highlight = document.getElementById(this.dropdownId).firstChild.firstChild.lastChild;
            else 
            {
                highlight.removeAttribute("id");
                if (highlight.previousSibling)
                {
                    if (escape(highlight.previousSibling.firstChild.data) == "%A0")
						highlight = highlight.previousSibling.previousSibling;
					else
						highlight = highlight.previousSibling;
                }
            }

            if (highlight) 
            {
                highlight.setAttribute("id","DropDownActive");
                var res = document.getElementById(this.dropdownId);
                if (highlight.offsetTop < res.scrollTop)
                    res.scrollTop = highlight.offsetTop;
            }
            
            if (!this.isIE)
                event.preventDefault();
            if (highlight)
                this.SelectionChanged(highlight.firstChild.data);
        } 
        else if (event.keyCode == 27) 
        {
            highlight = document.getElementById("DropDownActive");
            if (highlight)
                highlight.removeAttribute("id");
            if (document.all)
                this.closeShim(document.getElementById(this.dropdownId));
            document.getElementById(this.dropdownId).style.display = "none";
        }
        else
            this.Start(event);
    }

    this.Start = function(evt) 
    {
        if (this.timer) 
            window.clearTimeout(this.timer);

        var keyCode = document.layers ? evt.which : document.all ? evt.keyCode : evt.keyCode;
        if (keyCode != 13)
        {
            var thisObj = this;
            this.timer = window.setTimeout(function() { thisObj.Search(); }, 200);
        }
    }

    this.Search = function() 
    {
        var query = document.getElementById(this.anchorControlId).value;
        if (this.lastQuery != query) 
        {     
            if (this.httpReq && this.httpReq.readyState < 4) 
                this.httpReq.abort();
            if (query == "") 
            {
                this.lastQuery = "";
                this.hideDropDown();
                return false;
            }
            if (window.XMLHttpRequest) 
            {
            } 
            else if (window.ActiveXObject) 
                this.httpReq = new ActiveXObject("Microsoft.XMLHTTP");
            var thisObj = this;
            this.httpReq.onreadystatechange= function () { thisObj.readyStateChange(); };
            this.httpReq.open("GET", this.url + encodeURIComponent(query));
            this.httpReq.setRequestHeader("If-Modified-Since", "Sat, 1 Jan 2000 00:00:00 GMT");
            this.lastQuery = query;
            this.httpReq.send(null);
        }
    }

    this.readyStateChange = function() 
    {
        if (this.httpReq.readyState == 4 && this.httpReq.responseText != "") 
        {     
            var inner = document.getElementById(this.dropdownId + "_inner");
            var xml = this.httpReq.responseXML.documentElement;
			var ds = "", els = "";
			if (document.all)
                ds = "style='width:200px'";
			var items = this.GetItems(xml);
            
			var html = "<div class='DropDownResults' " + ds + ">";	
            
			for(var i = 0; i < items.items.length; i++)
			{
				if (document.all)
					html += "<div style='width:200px; ";
				else
					html += "<div style='white-space: nowrap; "
				html += items.styles[i] + "' onmouseover='" + this.instanceName + ".dropdownHover(this)' onclick='" + this.instanceName + ".dropdownClicked(this)'>" + items.items[i] + "</div>";
			}
            
			if (items.items.length > 0)
			{
				if ((this.Logged && this.Logged == true) && !(this.isipuser && this.isipuser == true))
				{
					html += "<div style='white-space: nowrap;'>&nbsp;</div>";
					if (document.all)
						html += "<div style='width:200px; ";
					else
						html += "<div style='white-space: nowrap; "

					html += "' onmouseover='" + this.instanceName + ".dropdownHover(this)' onclick='" + this.instanceName + ".dropdownClicked(this)'>" + this.turnoffMessage1 + "</div>";
					if (document.all)
						html += "<div style='width:200px; ";
					else
						html += "<div style='white-space: nowrap; "					
					html += "'>" + this.turnoffMessage2 + "</div>";
				}
			}
            
			html += "</div>";
			inner.innerHTML = html;

			var ddown = document.getElementById(this.dropdownId);
			
			if (items.items.length > 0)
			{
				ddown.style.display = "block";
				if (document.all)
					this.openShim(ddown);
			}
			else
			{
				ddown.style.display = "none";
				if (document.all)
                    this.closeShim(ddown);
			}
        }
    }
      
    this.dropdownHover = function(el) 
    {
        highlight = document.getElementById("DropDownActive");
        if (highlight)
            highlight.removeAttribute("id");
        el.setAttribute("id", "DropDownActive");
    }

    this.dropdownClicked = function(el) 
    {
        highlight = document.getElementById("DropDownActive");
        if (el.firstChild.data == this.turnoffMessage1)
		{
            this.Hide();
			if (this.TurnOff)				
                this.TurnOff();
        }
		else if (el.firstChild.data != this.turnoffMessage2)
		{
            if (highlight)
                highlight.removeAttribute("id");
            el.setAttribute("id","DropDownActive");
				return this.Clicked(el.firstChild.data);
        }
    }
      
    //Creates a new shim for the dropdown
    this.createShim = function(dropdown)
    {
        if (dropdown == null)
            return null;

        var shim = document.createElement("<iframe scrolling='no' frameborder='0'"+
                                          "style='z-index: 900; position:absolute; top:0px;"+
                                          "left:0px; display:none'></iframe>"); 
        shim.name = this.getShimId(dropdown);
        shim.id = this.getShimId(dropdown);
        //Unremark this line if you need your menus to be transparent for some reason
        //shim.style.filter="progid:DXImageTransform.Microsoft.Alpha(style=0,opacity=0)";

        if (dropdown.offsetParent==null || dropdown.offsetParent.id=="") 
            window.document.body.appendChild(shim);
        else 
            dropdown.offsetParent.appendChild(shim); 

        return shim;
    }
    
    //Creates an id for the shim based on the dropdown id
    this.getShimId = function(dropdown)
    {
        if (dropdown.id == null)
            return "__shim";
        return "__shim"+dropdown.id;
    }

    //Returns the shim for a specific dropdown
    this.getShim = function(dropdown)
    {
        return document.getElementById(this.getShimId(dropdown));
    }
      
    //Opens a shim, if no shim exists for the menu, one is created
    this.openShim = function(dropdown)
    {           
        if (dropdown==null) 
            return;
        var shim = this.getShim(dropdown);
        if (shim == null)
            shim = this.createShim(dropdown,this.getShimId(dropdown));
          
        //Change menu zIndex so shim can work with it
        dropdown.style.zIndex = 1000;
          
        var width = dropdown.offsetWidth;
        var height = dropdown.offsetHeight;
    
        shim.style.width = width;
        shim.style.height = height;
        shim.style.left = findPosX(dropdown) + "px";
        shim.style.top = findPosY(dropdown) + "px";
        shim.style.zIndex = dropdown.style.zIndex - 1;
        shim.style.position = "absolute";
        shim.style.display = "block";
    }

    //Closes the shim associated with the dropdown
    this.closeShim = function(dropdown)
    {
        if (dropdown == null)
            return;
        var shim = this.getShim(dropdown);
        if (shim != null)
            shim.style.display = "none";
    }
}
