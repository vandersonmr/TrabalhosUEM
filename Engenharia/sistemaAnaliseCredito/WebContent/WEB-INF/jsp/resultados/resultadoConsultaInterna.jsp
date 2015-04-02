<%-- 
    Document   : login.jsp
    Created on : 16/05/2013, 17:22:41
    Author     : vanderson
--%>

<%@page contentType="text/html" pageEncoding="UTF-8"%>
<%@ taglib prefix="fmt" uri="http://java.sun.com/jsp/jstl/fmt" %>
<%@ taglib prefix="c" uri="http://java.sun.com/jsp/jstl/core" %>
<!DOCTYPE html>
<html>
    <head>
        <style>
            @import url("/WEB-INF/style.css");
        </style>
        <meta http-equiv="Content-Type" content="text/html; charset=UTF-8">
        <title>Sistema de Análise de Crédito</title>
    </head>
    <body>


            <fieldset>
                <legend>RELATÓRIO DE COMPORTAMENTO EM NEGÓCIOS</legend>


                <div>
                    <table>
                        <tbody>
                            <c:forEach items="${resultado}" var="valor">
                                <tr><td><h3>${valor.label} (${valor.value}%)<br>0% --------------------------------------------------------50%--------------------------------------------------------- 100%</h3></tr>
                                <tr>
                                    <td><progress value="${valor.value}" max="100" ></progress></td>
                                </tr>
                            </c:forEach>
                        </tbody>
                    </table>
                </div>
                <input type="submit" onClick="window.history.back()" class="btn" value="Voltar"><br>
                <br><br>
                Sistema de Análise de Crédito. 2013. Criado pela equipe <a href="sobre.html">Lobos</a>.
            </fieldset>


    </body>
</html>
