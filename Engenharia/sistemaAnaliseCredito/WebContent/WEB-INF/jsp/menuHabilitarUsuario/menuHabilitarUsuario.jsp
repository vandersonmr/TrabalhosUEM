<%-- 
    Document   : menuConsultaExterna
    Created on : 16/05/2013, 20:54:11
    Author     : vanderson
--%>

<%@page contentType="text/html" pageEncoding="UTF-8"%>
<!DOCTYPE html>
<html>
    <head>
        <script src="http://ajax.googleapis.com/ajax/libs/jquery/1.10.2/jquery.min.js" ></script>
        <script type="text/javascript" src="http://igorescobar.github.io/jQuery-Mask-Plugin/js/jquery.mask.min.js"></script>
        <script src="./mascaras.js"></script>
        <meta http-equiv="Content-Type" content="text/html; charset=UTF-8">
        <title>Sistema de Análise de Crédito</title>
        <style>
            @import url("/WEB-INF/style.css");
        </style>
    </head>
    <body>
        <ul id="menu">
            <li>
                <a href="${pageContext.request.contextPath}/menuAdmin">Home</a>
            </li>
            <li>
                <a href="${pageContext.request.contextPath}/resultadoRelatorio">Relatório</a>
            </li>
            <li><a href="${pageContext.request.contextPath}/menuNovoCadastro">Cadastrar lojista</a></li>
            <li>
                <a href="${pageContext.request.contextPath}/menuDesabilitarUsuario">Desabilitar Lojista</a>
            </li>
            <li>
                <a href="${pageContext.request.contextPath}/menuHabilitarUsuario">Habilitar Lojista</a>
            </li>
            <li>
                <a href="${pageContext.request.contextPath}/logout">Logout</a>
            <li><br><br>
            <li><a href="ajuda.html">Ajuda</a></li>
        </ul>
        <form action="${pageContext.request.contextPath}/habilitarUsuario" method="post">
            <fieldset>
                <legend><h1>Habilitar afiliados já cadastrados</h1></legend>

                <li>
                    <label> Email*: </label><input name="lojista.email" required/>
                </li>
                <br><br>
                <li>
                    <input type="submit"  class="btn" value="Habilitar Cadastro"><br>
                <spam class="required_notification">Itens com * são obrigatórios.</spam>
                </li>
                <br><br>
                Sistema de Análise de Crédito. 2013. Criado pela equipe <a href="sobre.html">Lobos</a>.
            </fieldset>
        </form>
    </body>
</html>
