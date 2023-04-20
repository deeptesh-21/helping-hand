<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <meta http-equiv="X-UA-Compatible" content="IE=edge">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <link rel="stylesheet" href="https://cdn.jsdelivr.net/npm/bootstrap@5.3.0-alpha3/dist/css/bootstrap.min.css">
    <script src="https://ajax.googleapis.com/ajax/libs/jquery/3.6.3/jquery.min.js"></script>
    <title>Document</title>
</head>
<body>
    <span class="demo1"></span>
    <span class="demo2"></span>

    <script>
        function updateReading() { //just displaying data from json continuously
            $.ajax({
                url: './gpsdata.json',
                dataType: 'json',
                type: 'POST',
                success: function(data) {
                    console.log(data);
                    $('#demo1').text(data.longitude);
                    $('#demo2').html(data.longitude);
                }
            });
        }

        setInterval(updateReading, 2000);
    </script>
</body>
</html>