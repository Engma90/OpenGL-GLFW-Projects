using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;

public class CarBehaviourScript : MonoBehaviour {

    public static float carSpeed = 0f;
    float Score = 0;
	float turnSpeed = 20.0f;
    Text txt;

    public Camera FCam, BCam;
    public KeyCode TKey;
    public bool camSwitch = false;


    // Use this for initialization
    void Start () {
        //txt = gameObject.GetComponent<Text>();
        txt = GameObject.Find("Canvas").GetComponentInChildren<Text>();


        FCam = GetComponentsInChildren<Camera>()[0];
        BCam = GetComponentsInChildren<Camera>()[1];
        TKey = KeyCode.T;
        FCam.gameObject.SetActive(camSwitch);
        BCam.gameObject.SetActive(!camSwitch);
    }

	// Update is called once per frame
	void Update () {

        if (Input.GetKeyDown(TKey))
        {
            camSwitch = !camSwitch;
            FCam.gameObject.SetActive(camSwitch);
            BCam.gameObject.SetActive(!camSwitch);
        }

        if (transform.position.y < 1)
        {

            transform.position = new Vector3(
                transform.position.x,
                1,
                transform.position.z);//GameObject.Find("Car").transform.position.z +
        }

        Vector3 move = new Vector3(Input.GetAxis("Horizontal"), 0, 0);
		transform.position += move * turnSpeed * Time.deltaTime;
        if (transform.position.x < -4)
        {
            transform.position = new Vector3(-4, transform.position.y, transform.position.z);
        }

        if (transform.position.x > 4)
        {
            transform.position = new Vector3(4, transform.position.y, transform.position.z);
        }

        txt.text = "Speed : " + ((int)carSpeed).ToString() + " Score : " + Score.ToString();

    }

    void OnTriggerEnter(Collider other)
    {
        if(other.name == "Box")
        {
            carSpeed -= 10;
            if (carSpeed < 0)
            {
                carSpeed = 0;
            }

        }

        else if (other.name == "Gift")
        {
            Score++;
        }

        
    }
}
