$(
    $(function() {
        var token = $.cookie("token");
        if (token == null) {
            location.href = baseUrl + "jsp/login/login.jsp";
        }
        $("#logout").click(function() {
            $.ajax({
                url : baseUrl + 'api/user/logout',
                type : 'POST',
                contentType : 'application/json',
                dataType : 'json',
                headers : {"authorization": token},
                complete : function(XHR, TS) {
                    if (TS == "success") {
                        var ar = JSON.parse(XHR.responseText);
                        if (ar.code == 100) {
                        } else {
                            alert(ar.message);
                        }
                    } else {
                        alert("退出登录失败");
                    }
                    $.cookie("token", '', {path:'/'});
                    window.location.href= baseUrl + "jsp/login/login.jsp";
                }
            });
        })

    })

)