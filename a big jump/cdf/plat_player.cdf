object Plat_Player {
	float jumpHeight            1.0
	float timeToApex            0.5
	float movementSpeed        10.0
	float acceleration         10.0
	float terminalVelocity      3.0
	float neutralJumpDistance   3.0

	states {
		Airborne: PlatPlayer_GroundedMovement
			NULL -1
		Ground: PlatPlayer_GroundedMovement
			NULL -1
		Sliding:
			NULL -1
		GroundPound:
			NULL -1
		LongJump:
			NULL -1
		DoubleJump:
			NULL -1
		SideJump:
			NULL -1
		Running:
			NULL -1
	}
	
	a_events {
		jump
		crouch
	}
	
	events {
		land
	}
	
	transitions {
		Ground (jump)        Airborne
		Ground (jump|crouch) HighJump
		Running(jump|crouch) LongJump
	}
}
