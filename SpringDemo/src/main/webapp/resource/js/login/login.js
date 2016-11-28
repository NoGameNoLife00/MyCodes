$(
    function() {
    $('input').keyup(function (event) {
        if (event.keyCode == "13") {
            $("#btnLogin").click();
            return false;
        }
    });

    $("#btnLogin").click(function() {
        var param = {
            username : $("#username").val(),
            password : $("#password").val()
        };
        $.ajax({
            url : 'api/user/login',
            type : 'POST',
            contentType : 'application/json',
            data : JSON.stringify(param),
            dataType : 'json',
            complete : function(XHR, TS) {
                if (TS == "success") {
                    var ar = JSON.parse(XHR.responseText);
                    if (ar.code == 100) {
                        // ´æ´¢token
                        //setCookie("token", ar.data.username + "_" + ar.data.token, 1);
                        $.cookie("token", ar.data.username + "_" + ar.data.token, {expires: 1, path: "/"});
                        window.location.href = baseUrl + "jsp/index.jsp";
                    } else {
                        alert(ar.message);
                    }

                }
            }
        });
    })

});

function setCookie(name,value,expiredays)
{
    var exdate=new Date()
    exdate.setDate(exdate.getDate()+expiredays)
    var ck = name+ "=" + escape(value) +
        ((expiredays==null) ? "" : ";expires="+exdate.toGMTString()) +
        ";path=/;domain=" + window.location.host;
    document.cookie = ck;
}

function getCookie(name)
{
    if (document.cookie.length>0)
    {
        c_start=document.cookie.indexOf(name + "=")
        if (c_start!=-1)
        {
            c_start=c_start + name.length+1
            c_end=document.cookie.indexOf(";",c_start)
            if (c_end==-1) c_end=document.cookie.length
            return unescape(document.cookie.substring(c_start,c_end))
        }
    }
    return ""
}

function delCookie(name)
{
    var exp = new Date();
    exp.setTime(exp.getTime() - 1);
    var cval=getCookie(name);
    if(cval!=null)
        document.cookie= name + "="+cval+";expires="+exp.toGMTString();
}