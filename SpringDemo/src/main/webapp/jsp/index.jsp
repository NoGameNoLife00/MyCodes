<?xml version="1.0" encoding="GB2312" ?>
<%@ page language="java" contentType="text/html; charset=GB2312"
         pageEncoding="GB2312"%>
<%
    String path = request.getContextPath();
    String basePath = request.getScheme() + "://"
            + request.getServerName() + ":" + request.getServerPort()
            + path + "/";
%>

<!DOCTYPE html>

<html>
<head>
    <base href="<%=basePath%>">
    <title>SpringDome</title>
    <meta http-equiv="X-UA-Compatible" content="IE=edge,Chrome=1" />
    <meta http-equiv="X-UA-Compatible" content="IE=9" />
    <!--[if lt IE 9]>
    <script src="static/js/html5shiv.min.js"></script>
    <script src="static/js/respond.min.js"></script>
    <![endif]-->

    <meta http-equiv="Content-Type" content="text/html; charset=gb2312">
    <link rel="stylesheet" href="static/css/bootstrap.min.css">

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
    <script type="text/javascript" src="resource/js/index.js"  charset="gb2312"></script>

</head>


<body>

    <nav class="navbar navbar-default" role="navigation">
        <div class="container-fluid">
            <!-- Brand and toggle get grouped for better mobile display -->
            <div class="navbar-header">
                <button type="button" class="navbar-toggle collapsed" data-toggle="collapse" data-target="#bs-example-navbar-collapse-1">
                    <span class="sr-only">Toggle navigation</span>
                    <span class="icon-bar"></span>
                    <span class="icon-bar"></span>
                    <span class="icon-bar"></span>
                </button>
                <a class="navbar-brand" href="#">Brand</a>
            </div>

            <!-- Collect the nav links, forms, and other content for toggling -->
            <div class="collapse navbar-collapse" id="bs-example-navbar-collapse-1">
                <ul class="nav navbar-nav">
                    <li class="active"><a href="#">Link</a></li>
                    <li><a href="#">Link</a></li>
                    <li class="dropdown">
                        <a href="#" class="dropdown-toggle" data-toggle="dropdown">Dropdown <span class="caret"></span></a>
                        <ul class="dropdown-menu" role="menu">
                            <li><a href="#">Action</a></li>
                            <li><a href="#">Another action</a></li>
                            <li><a href="#">Something else here</a></li>
                            <li class="divider"></li>
                            <li><a href="#">Separated link</a></li>
                            <li class="divider"></li>
                            <li><a href="#">One more separated link</a></li>
                        </ul>
                    </li>
                </ul>
                <form class="navbar-form navbar-left" role="search">
                    <div class="form-group">
                        <input type="text" class="form-control" placeholder="Search">
                    </div>
                    <button type="submit" class="btn btn-default">Submit</button>
                </form>
                <ul class="nav navbar-nav navbar-right">
                    <li><a href="#">Link</a></li>
                    <li><a id="logout">退出登录</a></li>
                </ul>
            </div><!-- /.navbar-collapse -->
        </div><!-- /.container-fluid -->
    </nav>

    Hello world！

</body>
</html>
