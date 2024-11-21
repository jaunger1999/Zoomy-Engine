object Plat_Player {
	float jumpHeight            1.0
	float timeToApex            0.5
	float movementSpeed        10.0
	float acceleration         10.0
	float terminalVelocity      3.0
	float neutralJumpDistance   3.0

	states {
		Airborne:
		Ground: PlatPlayer_GroundedMovement
		Sliding:
		GroundPound:
		LongJump:
		DoubleJump:
		SideJump:
		Running:
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