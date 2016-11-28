<?xml version="1.0" encoding="GB2312" ?>
<%@ page language="java" contentType="text/html; charset=GB2312"
         pageEncoding="GB2312"%>

<%@ include file="../config/config.jsp"%>
<base href="<%=basePath%>">

<!DOCTYPE html>
<html>
<head>
    <title>Login</title>
    <meta http-equiv="Content-Type" content="text/html; charset=gb2312">
    <mate name="viewport" content="width=device-width, intial-scale=1.0"></mate>
    <meta http-equiv="X-UA-Compatible" content="IE=edge,Chrome=1" />
    <meta http-equiv="X-UA-Compatible" content="IE=9" />
    <!--[if lt IE 9]>
    <script src="static/js/html5shiv.min.js"></script>
    <script src="static/js/respond.min.js"></script>
    <![endif]-->

    <link rel="stylesheet" href="static/css/bootstrap.min.css">

    <style type="text/css">
        input{
            margin-bottom: 3px;
        }
    </style>
</head>
<body>

<div class="container" style="width: 250px">
    <h2 class="form-signin-heading">登录</h2>
    <input id="username" type="text" class="form-control" placeholder="User name" required autofocus>
    <input id="password" type="password" class="form-control" placeholder="Password" required>
    <button id="btnLogin" class="btn btn-lg btn-primary btn-block">登录</button>
</div>

<script type="text/javascript" src="static/js/jquery.min.js"></script>
<script type="text/javascript" src="static/js/jquery.cookie.js"></script>
<script type="text/javascript" src="static/js/bootstrap.min.js"></script>
<script type="text/javascript" src="static/js/jquery.placeholder.js"></script>
<script type="text/javascript">
    var baseUrl = "<%=basePath%>";
    $(function () {
        $('input, textarea').placeholder();
    });
</script>
<script type="text/javascript" src="resource/js/login/login.js"></script>
</body>

</html>