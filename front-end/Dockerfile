# Use a imagem base do Nginx
FROM nginx:alpine

COPY . /usr/share/nginx/html

COPY nginx.conf /etc/nginx/conf.d/default.conf

# Comando de entrada (não é necessário, já definido na imagem do Nginx)
# CMD ["nginx", "-g", "daemon off;"]