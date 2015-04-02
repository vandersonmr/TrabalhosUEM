<%-- 
    Document   : login.jsp
    Created on : 16/05/2013, 17:22:41
    Author     : vanderson
--%>

<%@page contentType="text/html" pageEncoding="UTF-8"%>
<!DOCTYPE html>
<html>
    <head>
        <script src="/WEB-INF/sha256.js"></script>
        <style>
            @import url("/WEB-INF/style.css");
        </style>
        <meta http-equiv="Content-Type" content="text/html; charset=UTF-8">
        <title>Sistema de Análise de Crédito</title>
    </head>
    <body>
        <h3 style="color: red;margin-left: auto; margin-right: auto" align="center">${error}</h3>
        <form  id="loginForm"  action="${pageContext.request.contextPath}/autenticar" method="post" autocomplete="on" >
            <fieldset>
                <legend><h1>Log in</h1></legend>

                <label for="username">Seu email ou usuário: </label>
                <input type="text" name="lojista.email"/>
                <br>
                <label for="password">Sua senha: </label>
                <input type="password" id ="pass" name="lojista.pass"/>


                <p class="login button">
                    <input type="submit" class="btn" value="Logar" 
                           onClick="document.getElementById('pass').value
                                       =new jsSHA(document.getElementById('pass')
                                       .value, 'TEXT').getHash('SHA-256', 'HEX');
                                       document.forms['loginForm'].submit();"/>
                </p>
                
                <p class="change_link">
                    Não é um membro ainda?
                    <a href="/WEB-INF/vendas.html" class="to_register">Junte-se</a>
                </p>
                <br>
                <center>    Sistema de Análise de Crédito. 2013. Criado pela equipe <a href="sobre.html">Lobos</a>.</center>
            </fieldset>
        </form>

    </body>
</html>
