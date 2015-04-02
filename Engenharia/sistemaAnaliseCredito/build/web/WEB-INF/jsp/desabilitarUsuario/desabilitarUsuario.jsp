<%-- 
    Document   : menuConsultaExterna
    Created on : 16/05/2013, 20:54:11
    Author     : vanderson
--%>

<%@page contentType="text/html" pageEncoding="UTF-8"%>
<!DOCTYPE html>
<html>
    <head>
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
                <a href="${pageContext.request.contextPath}/menu">Relatório</a>
            </li>
            <li>
                <a href="${pageContext.request.contextPath}/menu">Cadastrar Lojista</a>
            </li>
            <li>
                <a href="${pageContext.request.contextPath}/menuDesabilitarUsuario">Desabilitar Lojista</a>
            </li>
            <li>
                <a href="${pageContext.request.contextPath}/logout">Logout</a>
            <li><br><br>
                     <li><a href="ajuda.html">Ajuda</a></li>
        </ul>
        <form action="${pageContext.request.contextPath}/desabilitarUsuario">
            <fieldset>
                <legend><h1>Buscar afiliados já cadastrados</h1></legend>

                <li>
                    <label> Email*: </label><input name="lojista.cpf" required>
                </li>
                <br><br>
                <li>
                    <input type="submit"  class="btn" value="Buscar Cadastro"><br>
                <spam class="required_notification">Itens com * são obrigatórios.</spam>
                </li>
                <br><br>
                Sistema de Análise de Crédito. 2013. Criado pela equipe <a href="sobre.html">Lobos</a>.
            </fieldset>
        </form>
    </body>
</html>
