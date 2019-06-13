#include <QtTest>
#include <Discogs.h>
#include <string>

class DiscogsTests: public QObject
{
    Q_OBJECT
private slots:
    void requestFromEanTest();
    void requestFromReleaseIdTest();
};

void DiscogsTests::requestFromEanTest()
{
    // Use an EAN that really exists
    QString ean("0190759042120");
    // Create the object to test
    discinfo::Discogs testee;
    // Create a spy on the expected signal to be catched
    QSignalSpy spy(&testee, &discinfo::Discogs::success);
    QVERIFY(spy.isValid());
    // Perform the action expected to send the signal
    testee.requestFromEan(ean.toStdString());
    // Give some delay for the request to succeed
    QVERIFY(spy.wait());
    // It is expected to be emitted only once
    QCOMPARE(spy.count(), 1);
    // Get the signal arguments
    QList<QVariant> arguments = spy.takeFirst();
    // Check it is the expected answer
    QVERIFY(arguments.at(0).toString() == "{\"pagination\": {\"per_page\": 50, \"pages\": 1, \"page\": 1, \"urls\": {}, \"items\": 1}, \"results\": [{\"style\": [\"Chanson\", \"Dance-pop\", \"Synth-pop\"], \"barcode\": [\"1 90759 04212 0\", \"190759042120\", \"|| 19075904212 CD 56450 ||\", \"IFPI LN12\", \"IFPI 3721\", \"IFPI 3705\", \"|| 19075904212 DVD 56451 ||\", \"IFPI LN12\", \"IFPI 3711\", \"IFPI 3714\", \"SPPF\", \"BIEM/SDRM\", \"BMI\", \"19075904212/1\", \"19075904212/2\", \"EDV45\"], \"thumb\": \"https://img.discogs.com/nGXriOGfKzPG62Dds4Y88cZxeo8=/fit-in/150x150/filters:strip_icc():format(jpeg):mode_rgb():quality(40)/discogs-images/R-12870245-1552759913-2560.jpeg.jpg\", \"title\": \"Mylene Farmer* - D\\u00e9sob\\u00e9issance\", \"type\": \"release\", \"format\": [\"CD\", \"Album\", \"Reissue\", \"DVD\", \"DVD-Video\", \"PAL\", \"Box Set\"], \"uri\": \"/Mylene-Farmer-D%C3%A9sob%C3%A9issance/release/12870245\", \"community\": {\"want\": 17, \"have\": 202}, \"label\": [\"Stuffed Monkey\", \"#np\", \"Sony Music Entertainment France S.A.S.\", \"Sony Music Entertainment International Services GmbH\", \"Stuffed Monkey\", \"Stuffed Monkey\", \"Stuffed Monkey\", \"Artiworks\", \"District 6 France\", \"Modernsoul\", \"BMG Rights\", \"Universal Music Publishing\", \"Choke Industry\", \"Hit My Heart Songs\", \"Songs For KidInAKorner\", \"Songs Of Universal, Inc.\", \"Dear Cleveland Publishing\", \"Where Da Kasz At\", \"TCBInAFlashSongs\", \"Primary Wave Beats\", \"BMG Platinium Songs\", \"BMG Rights Management (US) LLC\", \"Studio Guillaume Tell\", \"Studio Motif Music\", \"Studio D.E.S.\", \"The Exchange Mike Marsh Mastering\", \"La Villa Mastering\", \"Boldatwork\"], \"country\": \"France\", \"cover_image\": \"https://img.discogs.com/zQhdQQ-AIt62TaXqLQpKb2Rr3rQ=/fit-in/600x564/filters:strip_icc():format(jpeg):mode_rgb():quality(90)/discogs-images/R-12870245-1552759913-2560.jpeg.jpg\", \"catno\": \"19075904212\", \"master_url\": \"https://api.discogs.com/masters/1426509\", \"year\": \"2018\", \"genre\": [\"Electronic\", \"Pop\"], \"resource_url\": \"https://api.discogs.com/releases/12870245\", \"master_id\": 1426509, \"format_quantity\": 2, \"id\": 12870245}]}");
}

void DiscogsTests::requestFromReleaseIdTest()
{
    // Use an EAN that really exists
    QString releaseId("000000");
    // Create the object to test
    discinfo::Discogs testee;
    // Create a spy on the expected signal to be catched
    QSignalSpy spy(&testee, &discinfo::Discogs::success);
    QVERIFY(spy.isValid());
    // Perform the action expected to send the signal
    testee.requestFromReleaseId(releaseId.toStdString());
    // Give some delay for the request to succeed
    QVERIFY(spy.wait());
    // It is expected to be emitted only once
    QCOMPARE(spy.count(), 1);
    // Get the signal arguments
    QList<QVariant> arguments = spy.takeFirst();
    // Check it is the expected answer
    QVERIFY(arguments.at(0).toString() == "{\"message\": \"Release not found.\"}");
}


QTEST_MAIN(DiscogsTests)
#include "DiscogsTests.moc"
