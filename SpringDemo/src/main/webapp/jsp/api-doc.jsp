<%@ page language="java" contentType="text/html; charset=ISO-8859-1"
    pageEncoding="GB2312"%>
<!DOCTYPE html PUBLIC "-//W3C//DTD HTML 4.01 Transitional//EN" "http://www.w3.org/TR/html4/loose.dtd">
<html>
<head>
    <title>Swagger UI</title>
    <link rel="icon" type="image/png" href="../static/images/favicon-32x32.png" sizes="32x32" />
    <link rel="icon" type="image/png" href="../static/images/favicon-16x16.png" sizes="16x16" />
    <link href='../static/css/typography.css' media='screen' rel='stylesheet' type='text/css'/>
    <link href='../static/css/reset.css' media='screen' rel='stylesheet' type='text/css'/>
    <link href='../static/css/screen.css' media='screen' rel='stylesheet' type='text/css'/>
    <link href='../static/css/reset.css' media='print' rel='stylesheet' type='text/css'/>
    <link href='../static/css/print.css' media='print' rel='stylesheet' type='text/css'/>
    <script src='../static/js/jquery-1.8.0.min.js' type='text/javascript'></script>
    <script src='../static/js/jquery.slideto.min.js' type='text/javascript'></script>
    <script src='../static/js/jquery.wiggle.min.js' type='text/javascript'></script>
    <script src='../static/js/jquery.ba-bbq.min.js' type='text/javascript'></script>
    <script src='../static/js/handlebars-2.0.0.js' type='text/javascript'></script>
    <script src='../static/js/underscore-min.js' type='text/javascript'></script>
    <script src='../static/js/backbone-min.js' type='text/javascript'></script>
    <script src='../static/js/swagger-ui.js' type='text/javascript'></script>
    <script src='../static/js/highlight.7.3.pack.js' type='text/javascript'></script>
    <script src='../static/js/marked.js' type='text/javascript'></script>
    <script src='../static/js/swagger-oauth.js' type='text/javascript'></script>
</head>
<body class="swagger-section">
<div id='header'>
    <div class="swagger-ui-wrap">
        <a id="logo" href="http://swagger.io">swagger</a>
        <form id='api_selector'>
            <div class='input'><input placeholder="http://example.com/api" id="input_baseUrl" name="baseUrl" type="text"/></div>
            <div class='input'><input placeholder="api_key" id="input_apiKey" name="apiKey" type="text"/></div>
            <div class='input'><a id="explore" href="#">Explore</a></div>
        </form>
    </div>
</div>

<div id="message-bar" class="swagger-ui-wrap">&nbsp;</div>
<div id="swagger-ui-container" class="swagger-ui-wrap"></div>
</body>
<script type="text/javascript">
    $(function () {
        var url = window.location.search.match(/url=([^&]+)/);
        if (url && url.length > 1) {
            url = decodeURIComponent(url[1]);
        } else {
            url = "http://" + window.location.host + "/SpringDemo/api-docs";
        }
        window.swaggerUi = new SwaggerUi({
            url: url,
            dom_id: "swagger-ui-container",
            supportedSubmitMethods: ['get', 'post', 'put', 'delete', 'patch'],
            onComplete: function(swaggerApi, swaggerUi){
                if(typeof initOAuth == "function") {
                    initOAuth({
                        clientId: "your-client-id",
                        realm: "your-realms",
                        appName: "your-app-name"
                    });
                }

                $('pre code').each(function(i, e) {
                    hljs.highlightBlock(e)
                });

                addApiKeyAuthorization();
            },
            onFailure: function(data) {
                log("Unable to Load SwaggerUI");
            },
            docExpansion: "none",
            apisSorter: "alpha",
            showRequestHeaders: false
        });

        function addApiKeyAuthorization(){
            var key = encodeURIComponent($('#input_apiKey')[0].value);
            if(key && key.trim() != "") {
                var apiKeyAuth = new SwaggerClient.ApiKeyAuthorization("api_key", key, "query");
                window.swaggerUi.api.clientAuthorizations.add("api_key", apiKeyAuth);
                log("added key " + key);
            }
        }

        $('#input_apiKey').change(addApiKeyAuthorization);

        // if you have an apiKey you would like to pre-populate on the page for demonstration purposes...
        /*
         var apiKey = "myApiKeyXXXX123456789";
         $('#input_apiKey').val(apiKey);
         */

        window.swaggerUi.load();

        function log() {
            if ('console' in window) {
                console.log.apply(console, arguments);
            }
        }
    });
</script>

</html>