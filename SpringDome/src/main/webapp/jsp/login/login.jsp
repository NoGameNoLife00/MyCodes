<?xml version="1.0" encoding="GB2312" ?>
<%@ page language="java" contentType="text/html; charset=GB2312"
         pageEncoding="GB2312"%>
<html>
<head>
    <title>Login</title>
    <meta http-equiv="Content-Type" content="text/html; charset=gb2312">
    <mate name="viewport" content="width=device-width, intial-scale=1.0"></mate>
    <link rel="stylesheet" href="../../static/css/bootstrap.min.css">
    <style type="text/css">
        .form-signin {
            max-width: 330px;
            padding: 15px;
            margin: 0 auto;
        }
        input{
            margin-bottom: 3px;
        }
    </style>
</head>
<body>

<div class="container">
    <h2 class="form-signin-heading">登录</h2>
    <input id="username" type="text" class="form-control" placeholder="User name" required autofocus>
    <input id="password" type="password" class="form-control" placeholder="Password" required>
    <button id="btnLogin" class="btn btn-lg btn-primary btn-block">登录</button>
</div>
<script type="text/javascript" src="../../static/js/jquery.min.js"></script>
<script type="text/javascript" src="../../static/js/jquery.cookie.js"></script>
<script type="text/javascript" src="../../static/js/bootstrap.min.js"></script>
<script type="text/javascript" src="../../resource/js/login/login.js"></script>
</body>

</html>