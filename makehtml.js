var fs = require("fs");
//var showdown = require('showdown');
var marked = require('marked');
//showdown.setOption('strikethrough', true);
var iconv = require('iconv-lite');

fs.readdir("./source/posts/", function(err, files) {
    if (err) console.error(err);
    files.forEach(function (file) { makehtml("./source/posts/" + file.toString(), "./posts/" + file.toString() + ".html", 
        "../styles.css", "../markdownStyles.css", "../posts.html", 0); });
});
makehtml("./source/pages/links.post", "./links.html", "./styles.css", "./markdownStyles.css", "./index.html", 1);
makehtml("./source/pages/about.post", "./about.html", "./styles.css", "./markdownStyles.css", "./index.html", 1);
makehtml("./source/pages/this.post", "./this.html", "./styles.css", "./markdownStyles.css", "./index.html", 1);

function makehtml(name, goal, styles, markdownstyles, returnto, type) {
    fs.readFile(name, 'binary', function(err, data) {
        if (err) console.error(err);
        var buf = new Buffer(data, 'binary');
        var str = iconv.decode(buf, 'gbk');
        fs.writeFileSync(goal, '<!DOCTYPE html>\n\
        <html>\n\
            <head>\n\
                <meta charset="utf-8"/>\n\
                <title>n-kw && n-c by others</title>\n\
                <link rel="stylesheet" type="text/css" href="' + styles + '"/>\n\
                <link rel="stylesheet" type="text/css" href="' + markdownstyles + '"/>\n\
                <link rel="stylesheet" href="https://cdn.bootcss.com/KaTeX/0.11.1/katex.min.css">\n\
                <script defer src="https://cdn.bootcss.com/KaTeX/0.11.1/katex.min.js"></script>\n\
                <script>\n\
                var katex_config = {\n\
                    delimiters: \n\
                    [\n\
                        {left: "$$", right: "$$", display: true},\n\
                        {left: "$", right: "$", display: false}\n\
                    ]\n\
                };\n\
                </script>\n\
                <script defer src="https://cdn.bootcss.com/KaTeX/0.11.1/contrib/auto-render.min.js" onload="renderMathInElement(document.body,katex_config)"></script>\n\
            </head>\n\
            <body>\n\
                <div class="body">\n\
                <p class="title">striving & singing</p>');
        //var converter = new showdown.Converter();
        //var html = converter.makeHtml(data.toString());
        //var header = /[^]+<!--more-->[\r\n]/.exec(data.toString()).toString().replace(/<!--more-->\n/, "");
        //var title = /title:[^]+[\r\n]date:/.exec(header).toString().replace(/date:/, "").replace(/title:/, "");
        //var date = /date:[^]+[\r\n]/.exec(header).toString().replace(/date:/, "");
        var text;
        if (type == 0) text = str.replace(/[^]+<!--more-->[\r\n]/, "");
        else if (type == 1) text = str;
        var html = marked(text);
        fs.appendFileSync(goal, html, function(err) {
            if (err) console.error(err);
        });
        fs.appendFileSync(goal, '<a href="' + returnto + '" class="link" style="display:block; text-align:center;">return</a>\n</div>\n</body>\n</html>', function(err) {
            if (err) console.error(err);
        });
    });
}