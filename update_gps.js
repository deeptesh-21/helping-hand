
function updateReading() { //just displaying data from json continuously
    $.ajax({
        url: './gpsdata.json',
        dataType: 'json',
        type: 'POST',
        success: function(data) {
            $('#demo1').text(data.latitude);
            $('#demo2').text(data.longitude);
        }
    });
}

setInterval(updateReading, 1000);